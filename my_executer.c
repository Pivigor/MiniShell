/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:52:17 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 22:52:18 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	my_exec_starter(t_command *cmd, t_shell *shell)
{
	int		i;
	char	*full_path;
	char	*temp;

	if (ft_strchr(cmd->args[0], '/') != NULL)
		execve(cmd->args[0], cmd->args, shell->env);
	else if (my_check_builtin(cmd, shell, 1) != 0)
		exit(0);
	else if (shell->path != NULL)
	{
		temp = ft_strjoin("/", cmd->args[0]);
		i = 0;
		while (shell->path[i] != NULL)
		{
			full_path = ft_strjoin(shell->path[i], temp);
			execve(full_path, cmd->args, shell->env);
			free(full_path);
			i++;
		}
		free(temp);
	}
	my_exec_error(cmd);
}

t_list	*my_main_proc(t_executor *ex, t_list *list)
{
	if (ex->fd_input_pipe != -1)
		close(ex->fd_input_pipe);
	ex->fd_input_pipe = -1;
	if (ex->cmd->push_pipe == 1)
	{
		ex->fd_input_pipe = ex->fd[STDIN_FILENO];
		close(ex->fd[STDOUT_FILENO]);
	}
	return (list->next);
}

void	my_child_proc(t_executor *ex, t_shell *shell)
{
	if (ex->cmd->push_pipe == 1)
	{
		dup2(ex->fd[STDOUT_FILENO], STDOUT_FILENO);
		close(ex->fd[STDOUT_FILENO]);
		close(ex->fd[STDIN_FILENO]);
	}
	if (ex->fd_input_pipe != -1)
	{
		dup2(ex->fd_input_pipe, STDIN_FILENO);
		close(ex->fd_input_pipe);
	}
	if (ex->cmd->input_fd != -1)
	{
		dup2(ex->cmd->input_fd, STDIN_FILENO);
		close(ex->cmd->input_fd);
	}
	if (ex->cmd->output_fd != -1)
	{
		dup2(ex->cmd->output_fd, STDOUT_FILENO);
		close(ex->cmd->output_fd);
	}
	my_exec_starter(ex->cmd, shell);
}

void	my_async_exec(t_list *list, t_shell *shell)
{
	t_executor	ex;

	ex.fd_input_pipe = -1;
	while (list != NULL)
	{
		ex.cmd = list->content;
		if (ex.cmd->args[0] == NULL)
			return ;
		if (ex.cmd->push_pipe == 1)
			pipe(ex.fd);
		ex.pid = fork();
		if (ex.pid != 0)
			list = my_main_proc(&ex, list);
		else
			my_child_proc(&ex, shell);
	}
	my_global_static(1, 1);
	while (wait(&shell->last_code) != -1)
		(void)0;
	my_global_static(1, 0);
}

void	my_cmd_controller(char *cmd, t_shell *shell)
{
	t_list	*list;

	list = my_cmd_parser(cmd, shell);
	if (!(ft_lstsize(list) == 1
			&& my_check_builtin(list->content, shell, 0) != 0))
		my_async_exec(list, shell);
	ft_lstclear(&list, my_free_cmd);
}
