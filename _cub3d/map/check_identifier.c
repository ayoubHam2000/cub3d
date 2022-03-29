/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:18:29 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 20:30:33 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valide_color(char *str)
{
	char	**colores;
	int		c;
	int		i;

	colores = ft_split(str, ',');
	i = 0;
	while (colores[i] && int_check(colores[i]))
	{
		c = ft_atoi(colores[i]);
		if (c < 0 || c > 255)
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

int	check_identifier(char *identifier, int type)
{
	int	i;

	i = 0;
	if (type < 4)
	{
		i = open(identifier, O_RDONLY);
		if (i < 0)
		{
			perror("Map");
			return (0);
		}
		else
			close(i);
	}
	else
	{
		return (is_valide_color(identifier));
	}
	return (1);
}
