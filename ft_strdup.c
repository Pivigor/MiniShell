/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:21:51 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 23:21:52 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int		i;
	char	*s;

	i = 0;
	while (src[i] != '\0')
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (s != 0)
	{
		i = 0;
		while (src[i] != '\0')
		{
			s[i] = src[i];
			i++;
		}
		s[i] = '\0';
	}
	return (s);
}