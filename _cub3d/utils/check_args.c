/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:57:42 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/28 17:59:08 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extention(char *path)
{
	//TODO: dire checko l extention cub
	return (1);
}

static int	check_file(char *file)
{
	//TODO: swba
	return (1);
}

int	check_arg(int ac, char **av)
{
	if (ac == 2)
	{
		if (check_extention(av[1]) && check_file(av[1]))
			return (1);
	}
	return (0);
}
