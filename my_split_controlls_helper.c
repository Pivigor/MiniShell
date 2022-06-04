/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split_controlls_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:45:12 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 22:45:12 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	my_split_size(char **split)
{
	int	size;

	size = 0;
	if (split == NULL)
		return (0);
	while (split[size] != NULL)
		size++;
	return (size);
}

void	my_print_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		printf("%s\n", split[i]);
		i++;
	}
}

char	**my_split_path(char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		if (ft_strlen(env[i]) >= 5 && env[i][0] == 'P' && env[i][1] == 'A'
			&& env[i][2] == 'T' && env[i][3] == 'H' && env[i][4] == '=')
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}
