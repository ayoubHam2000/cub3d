/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:09:54 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 22:14:43 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_surrounded_by_one(char **map)
{
	int	i;
	int	j;
	
	i = 1;
	j = 0;
	while (map[0][j] == '1')
		j++;
	if (map[0][j])
		return (0);
	while (map[i + 1])
	{
		if (!(map[i][0] == '1' && map[i][ft_strlen(map[i]) - 1] == '1'))
			return (0);
		i++;
	}
	j = 0;
	while (map[i][j] == '1')
		j++;
	if (map[i][j])
		return (0);
	return (1);
}

static int is_in_charset(char c, int *p)
{
	const char	set[] = "01NSEW\0";
	int			i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			break ;
		i++;
	}
	if (!set[i])
		return (0);
	if (set[i] == 'N' || set[i] == 'E' || set[i] == 'W' || set[i] == 'S')
		(*p)++;
	return (1);
}

int	check_map(char **map)
{
	int	i;
	int j;
	int	p;
	
	i = 0;
	p = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_in_charset(map[i][j], &p))
				return (0);
			j++;
		}
		i++;
	}
	if (i < 3 || p != 1)
		return (0);
	return (check_surrounded_by_one(map));
}
