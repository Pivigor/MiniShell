/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:22:08 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 23:22:09 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__SIZE_TYPE__	ft_strlen(const char *s)
{
	__SIZE_TYPE__	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
