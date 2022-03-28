/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:57:42 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/28 18:22:21 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extention(char *path)
{
	char *extention = ft_strrchr(path, '.');
	if(!extention || !ft_strcmp(extention, ".cub"))
	{
		ft_error("extension not matches\n");
		return (0);
	}
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
