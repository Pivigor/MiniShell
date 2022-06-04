/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:19:24 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 23:19:25 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	my_global_static(int mode, int value)
{
	static int	x;

	if (mode == 1)
		x = value;
	return (x);
}

void	my_cd_error(char *msg, t_shell *shell, int can_exit)
{
	char	*err_msg;

	err_msg = NULL;
	err_msg = ft_strjoin("cd: ", msg);
	perror(err_msg);
	free(err_msg);
	shell->last_code = 256;
	if (can_exit)
		exit(1);
}

void	my_cd_update(t_shell *shell)
{
	char	*new_pwd;
	char	*temp;

	new_pwd = NULL;
	temp = NULL;
	if (my_env_check(shell->env, "PWD"))
		shell->env = my_remove_split(shell->env, "PWD");
	temp = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", temp);
	shell->env = my_add_split(shell->env, new_pwd);
	free(temp);
}

void	my_builtin_cd(char **args, t_shell *shell, int can_exit)
{
	char	*home_path;

	if (args[1] != NULL)
	{
		if (chdir(args[1]) == -1)
			my_cd_error(args[1], shell, can_exit);
		else
			my_cd_update(shell);
	}
	else
	{
		home_path = my_env_find(shell->env, "HOME", shell->last_code);
		if (chdir(home_path) == -1)
			my_cd_error(home_path, shell, can_exit);
		else
			my_cd_update(shell);
		free(home_path);
	}
}

void	my_builtin_exit(char **args)
{
	if (args[1] != NULL)
		exit(ft_atoi(args[1]));
	else
		exit(0);
}
