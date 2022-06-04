/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split_controlls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:36:26 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 22:36:27 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	my_env_check(char **env, char *find)
{
	int	i;
	int	target_size;
	int	current_size;

	i = 0;
	target_size = ft_strlen(find);
	if (env == NULL)
		return (0);
	while (env[i] != NULL)
	{
		current_size = ft_strlen(env[i]);
		if (current_size >= target_size + 1
			&& ft_strncmp(env[i], find, target_size) == 0
			&& env[i][target_size] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*my_env_find(char **env, char *find, int last_code)
{
	int	i;
	int	target_size;
	int	current_size;

	i = 0;
	target_size = ft_strlen(find);
	if (find[0] == '?' && find[1] == '\0')
		return (ft_itoa(last_code));
	if (env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		current_size = ft_strlen(env[i]);
		if (current_size >= target_size + 1
			&& ft_strncmp(env[i], find, target_size) == 0
			&& env[i][target_size] == '=')
			return (ft_strdup(env[i] + target_size + 1));
		i++;
	}
	return (NULL);
}

char	**my_init_split(char **split)
{
	char	**new_split;
	int		size;
	int		i;

	size = my_split_size(split);
	new_split = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		new_split[i] = ft_strdup(split[i]);
		i++;
	}
	new_split[i] = NULL;
	return (new_split);
}

char	**my_add_split(char **split, char *new_elem)
{
	char	**new_split;
	int		size;
	int		i;

	size = my_split_size(split);
	new_split = malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (i < size)
	{
		new_split[i] = split[i];
		i++;
	}
	new_split[i] = new_elem;
	new_split[i + 1] = NULL;
	free(split);
	return (new_split);
}

char	**my_remove_split(char **split, char *del_elem)
{
	t_remove_split	rs;

	rs.size = my_split_size(split);
	rs.new_split = malloc(sizeof(char *) * rs.size);
	rs.offset = 0;
	rs.del_size = ft_strlen(del_elem);
	rs.i = 0;
	while (rs.i < rs.size - 1)
	{
		if (rs.offset == 0
			&& ft_strncmp(del_elem, split[rs.i], rs.del_size) == 0
			&& split[rs.i][rs.del_size] == '=')
		{
			rs.offset = 1;
			free(split[rs.i]);
		}
		rs.new_split[rs.i] = split[rs.i + rs.offset];
		rs.i++;
	}
	if (rs.offset == 0 && ft_strncmp(del_elem, split[rs.i], rs.del_size) == 0
		&& split[rs.i][rs.del_size] == '=')
		free(split[rs.i]);
	rs.new_split[rs.i] = NULL;
	free(split);
	return (rs.new_split);
}
