/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_status_solver_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:28:10 by jgarlic           #+#    #+#             */
/*   Updated: 2021/12/02 22:28:11 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	my_input_solver_part2(char *str)
{
	if (str == NULL)
	{
		write(STDERR_FILENO, "Error with input!\n", 18);
		exit(1);
	}
}
