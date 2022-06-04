/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:19:32 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 23:19:33 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	my_builtin_export(char **args, t_shell *shell)
{
	char	*eq;
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		eq = NULL;
		eq = ft_strchr(args[i], '=');
		if (eq != NULL)
		{
			*eq = '\0';
			if (my_env_check(shell->env, args[i]))
				shell->env = my_remove_split(shell->env, args[i]);
			*eq = '=';
			shell->env = my_add_split(shell->env, ft_strdup(args[i]));
		}
		i++;
	}
}

void	my_builtin_unset(char **args, t_shell *shell, int can_exit)
{
	char	*err_msg;
	int		i;
	char	*temp;

	err_msg = NULL;
	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL)
		{
			temp = ft_strjoin("unset: ", args[i]);
			err_msg = ft_strjoin(temp, ": invalid parameter name\n");
			write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
			free(temp);
			free(err_msg);
			shell->last_code = 256;
			if (can_exit)
				exit(1);
			else
				return ;
		}
		if (my_env_check(shell->env, args[i]))
			shell->env = my_remove_split(shell->env, args[i]);
		i++;
	}
}

void	my_builtin_env(char **args, t_shell *shell)
{
	if (args[1] == NULL)
	{
		my_print_split(shell->env);
	}
}

int	my_check_builtin1(t_command *cmd, t_shell *shell, int can_exit)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
	{
		my_builtin_cd(cmd->args, shell, can_exit);
		return (1);
	}
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	{
		my_builtin_exit(cmd->args);
		return (1);
	}
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
	{
		my_builtin_export(cmd->args, shell);
		return (1);
	}
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
	{
		my_builtin_unset(cmd->args, shell, can_exit);
		return (1);
	}
	return (0);
}

int	my_check_builtin(t_command *cmd, t_shell *shell, int can_exit)
{
	if (cmd->args == NULL || cmd->args[0] == NULL)
		return (0);
	if (my_check_builtin1(cmd, shell, can_exit))
		return (1);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
	{
		my_builtin_env(cmd->args, shell);
		return (1);
	}
	return (0);
}
