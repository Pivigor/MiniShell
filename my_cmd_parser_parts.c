/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cmd_parser_parts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:19:54 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/03 00:19:55 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	my_cmd_parser_part4(t_parser *p)
{
	if ((p->str[p->i] == '\'' && p->quote == 1)
		|| (p->str[p->i] == '\"' && p->quote == 2))
	{
		p->quote = 0;
		my_cut_char(&p->str, p->i--);
	}
}

void	my_cmd_parser_part3(t_parser *p)
{
	p->newline = readline("dquote> ");
	if (p->newline == NULL)
	{
		printf("Error with quote!\n");
		exit(0);
	}
	add_history(p->newline);
	my_str_append(&p->str, p->newline);
	my_str_append(&p->cmd, p->newline);
	free(p->newline);
	p->updated = 1;
}

void	my_cmd_parser_part2(t_parser *p)
{
	if (p->str[p->i] == '<' && p->str[p->i + 1] == '<')
		my_ss(p, my_st(p->str, p->i, &p->bword), 0, Input);
	else if (p->str[p->i] == '<')
		my_ss(p, my_st(p->str, p->i, &p->bword), 0, File);
	else if (p->str[p->i] == '>' && p->str[p->i + 1] == '>')
		my_ss(p, my_st(p->str, p->i, &p->bword), 0, Append);
	else if (p->str[p->i] == '>')
		my_ss(p, my_st(p->str, p->i, &p->bword), 0, Write);
	else if (p->str[p->i] == '\'')
	{
		p->quote = 1;
		my_cut_char(&p->str, p->i--);
	}
	else if (p->str[p->i] == '\"')
	{
		p->quote = 2;
		my_cut_char(&p->str, p->i--);
	}
}

void	my_cmd_parser_part1(t_parser *p)
{
	if (p->str[p->i] == ' ' && p->bword != -1)
		my_ss(p, my_st(p->str, p->i, &p->bword), 0, Dis);
	else if (p->str[p->i] == '|')
	{
		my_ss(p, my_st(p->str, p->i, &p->bword), 1, Dis);
		ft_lstadd_back(&p->list, ft_lstnew(my_init_cmd(NULL, 0)));
	}
	else if (p->str[p->i] == ';')
	{
		my_ss(p, my_st(p->str, p->i, &p->bword), 0, Dis);
		ft_lstadd_back(&p->list, ft_lstnew(my_init_cmd(NULL, 0)));
	}
	else
		my_cmd_parser_part2(p);
}

void	my_cmd_parser_part5(t_parser *p, t_shell *shell)
{
	while (p->str[p->i] != '\0')
	{
		if (my_is_spec(p->str[p->i]) == 0 && p->bword == -1)
			p->bword = p->i;
		if (p->quote == 0)
		{
			if (p->str[p->i] == '$')
			{
				p->str = my_var_solver(p->str, p->i, shell, p->quote);
				continue ;
			}
			else
				my_cmd_parser_part1(p);
		}
		else if (p->str[p->i] == '$' && p->quote == 2)
		{
			p->str = my_var_solver(p->str, p->i, shell, p->quote);
			continue ;
		}
		else
			my_cmd_parser_part4(p);
		p->i++;
	}
}
