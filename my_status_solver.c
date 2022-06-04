/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_status_solver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:21:31 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/03 00:21:33 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	my_file_solver(t_command *cmd, char *arg)
{
	cmd->input_state = File;
	cmd->input_arg = arg;
	if (cmd->input_fd != -1)
		close(cmd->input_fd);
	cmd->input_fd = open(arg, O_RDONLY);
	if (cmd->input_fd == -1)
	{
		perror(cmd->args[0]);
		exit(1);
	}
}

int	my_input_solver(t_command *cmd)
{
	int		fd[2];
	char	*str;

	pipe(fd);
	while (1)
	{
		str = readline("heredoc> ");
		my_input_solver_part2(str);
		if (ft_strlen(str) != ft_strlen(cmd->input_arg)
			|| ft_strncmp(str, cmd->input_arg, ft_strlen(str)) != 0)
		{
			write(fd[STDOUT_FILENO], str, ft_strlen(str));
			write(fd[STDOUT_FILENO], "\n", 1);
		}
		else
			break ;
		free(str);
		str = NULL;
	}
	free(str);
	close(fd[STDOUT_FILENO]);
	return (fd[STDIN_FILENO]);
}

void	my_write_solver(t_command *cmd, char *arg)
{
	cmd->output_state = Write;
	cmd->output_arg = arg;
	if (cmd->output_fd != -1)
		close(cmd->output_fd);
	cmd->output_fd = open(arg, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (cmd->output_fd == -1)
	{
		perror(cmd->args[0]);
		exit(1);
	}
}

void	my_append_solver(t_command *cmd, char *arg)
{
	cmd->output_state = Append;
	cmd->output_arg = arg;
	if (cmd->output_fd != -1)
		close(cmd->output_fd);
	cmd->output_fd = open(arg, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (cmd->output_fd == -1)
	{
		perror(cmd->args[0]);
		exit(1);
	}
}

// my_status_solver
void	my_ss(t_parser *p, char *arg, int pipe,
				t_pipe_state new_status)
{
	t_list		*lstlast;
	t_command	*cmdlast;

	lstlast = ft_lstlast(p->list);
	cmdlast = lstlast->content;
	if (pipe)
		cmdlast->push_pipe = 1;
	if (p->status == Dis)
		cmdlast->args = my_add_split(cmdlast->args, arg);
	if (p->status == File)
		my_file_solver(cmdlast, arg);
	if (p->status == Input)
	{
		cmdlast->input_state = Input;
		cmdlast->input_arg = arg;
		cmdlast->input_fd = my_input_solver(cmdlast);
	}
	if (p->status == Write)
		my_write_solver(cmdlast, arg);
	if (p->status == Append)
		my_append_solver(cmdlast, arg);
	if (new_status == Input || new_status == Append)
		p->i++;
	p->status = new_status;
}
