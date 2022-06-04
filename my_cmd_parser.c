/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cmd_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:22:50 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 23:22:51 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

t_command	*my_init_cmd(char **args, int pipe)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->args = args;
	command->input_state = Dis;
	command->input_fd = -1;
	command->input_arg = NULL;
	command->output_state = Dis;
	command->output_fd = -1;
	command->output_arg = NULL;
	command->push_pipe = pipe;
	return (command);
}

int	my_is_spec(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == ';' || c == '$')
		return (1);
	return (0);
}

t_parser	my_init_parser(char *cmd)
{
	t_parser	parser;

	parser.list = ft_lstnew(my_init_cmd(NULL, Dis));
	parser.cmd = cmd;
	parser.str = ft_strdup(cmd);
	parser.i = 0;
	parser.bword = -1;
	parser.quote = 0;
	parser.updated = 0;
	parser.status = Dis;
	return (parser);
}

void	my_str_append(char **str, char *append)
{
	char	*temp;

	temp = ft_strjoin(*str, "\n");
	free(*str);
	*str = ft_strjoin(temp, append);
	free(temp);
}

t_list	*my_cmd_parser(char *command, t_shell *shell)
{
	t_parser	p;

	p = my_init_parser(command);
	add_history(p.cmd);
	while (1)
	{
		my_cmd_parser_part5(&p, shell);
		if (p.quote == 0)
		{
			my_ss(&p, my_st(p.str, p.i, &p.bword), 0, Dis);
			break ;
		}
		else
			my_cmd_parser_part3(&p);
	}
	if (p.updated)
		add_history(p.cmd);
	free(p.cmd);
	free(p.str);
	return (p.list);
}
