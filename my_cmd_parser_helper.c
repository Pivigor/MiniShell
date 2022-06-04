/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cmd_parser_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:19:05 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/03 00:19:06 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	my_cut_char(char **str, int index)
{
	while ((*str)[index + 1] != '\0')
	{
		(*str)[index] = (*str)[index + 1];
		index++;
	}
	(*str)[index] = (*str)[index + 1];
}

// my_str_trim
char	*my_st(char *str, int index, int *bword)
{
	char	temp;
	char	*ret;

	ret = NULL;
	if (*bword != -1)
	{
		temp = str[index];
		str[index] = '\0';
		ret = ft_strdup(str + *bword);
		str[index] = temp;
		*bword = -1;
	}
	return (ret);
}

char	*my_var_helper(char *str, t_var_helper *vh, int quotes)
{
	char	*tempstr1;
	char	*tempstr2;
	char	*tempstr3;
	char	*newstr;
	char	*quote;

	quote = "";
	if (quotes == 0)
		quote = "\"";
	str[vh->i] = '\0';
	tempstr1 = ft_strjoin(str, quote);
	str[vh->i + vh->j] = vh->tempc;
	tempstr2 = ft_strjoin(tempstr1, vh->vr);
	tempstr3 = ft_strjoin(tempstr2, quote);
	newstr = ft_strjoin(tempstr3, str + vh->i + vh->j);
	free(str);
	free(vh->vr);
	free(tempstr1);
	free(tempstr2);
	free(tempstr3);
	return (newstr);
}

char	*my_var_solver(char *str, int i, t_shell *shell, int quotes)
{
	t_var_helper	vh;

	vh.i = i;
	vh.j = 1;
	vh.vr = NULL;
	while (1)
	{
		if (my_is_spec(str[vh.i + vh.j]) || str[vh.i + vh.j] == '"'
			|| str[vh.i + vh.j] == '\0')
		{
			vh.tempc = str[vh.i + vh.j];
			str[vh.i + vh.j] = '\0';
			vh.vr = my_env_find(shell->env, str + vh.i + 1,
					shell->last_code / 256);
			if (vh.vr == NULL)
				vh.vr = ft_strdup("\0");
			break ;
		}
		vh.j++;
	}
	if (vh.vr != NULL)
		return (my_var_helper(str, &vh, quotes));
	return (str);
}
