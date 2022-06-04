/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:22:39 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 23:22:41 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	my_free_shell(t_shell *shell)
{
	if (shell != NULL)
	{
		my_free_split(shell->env);
		if (shell->fd_pipe != -1)
			close(shell->fd_pipe);
		free(shell->path);
		free(shell);
	}
}

t_shell	*my_init_shell(char **env)
{
	t_shell	*shell;

	shell = NULL;
	shell = malloc(sizeof(t_shell));
	shell->i = 0;
	shell->fd_pipe = -1;
	shell->last_code = 0;
	shell->env = my_init_split(env);
	shell->path = my_split_path(env);
	return (shell);
}

void	c_quit(int sig)
{
	if (sig == SIGQUIT && my_global_static(0, 0) == 0)
		write(STDOUT_FILENO, "Quit: 3", 7);
	if (sig == SIGINT && my_global_static(0, 0) == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_ft(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, c_quit);
}

int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;
	char		*cmd;

	(void)argc;
	(void)argv;
	shell = my_init_shell(env);
	signal_ft();
	while (1)
	{
		cmd = readline("minishell>");
		if (cmd == NULL)
			exit(0);
		my_cmd_controller(cmd, shell);
	}
}
