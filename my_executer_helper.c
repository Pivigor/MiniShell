/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_executer_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:13:38 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 23:13:39 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	my_free_split(char **split)
{
	int	i;

	if (split != NULL)
	{
		i = 0;
		while (split[i] != NULL)
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

void	my_free_cmd(void *content)
{
	t_command	*cmd;

	if (content != NULL)
	{
		cmd = content;
		my_free_split(cmd->args);
		free(cmd->input_arg);
		free(cmd->output_arg);
		if (cmd->input_fd != -1)
			close(cmd->input_fd);
		if (cmd->output_fd != -1)
			close(cmd->output_fd);
		free(cmd);
	}
}

void	my_exec_error(t_command *cmd)
{
	if (errno == ENOENT)
	{
		printf("%s: Command not found\n", cmd->args[0]);
		exit(127);
	}
	perror(cmd->args[0]);
	if (errno == EACCES)
		exit(126);
	exit(1);
}
