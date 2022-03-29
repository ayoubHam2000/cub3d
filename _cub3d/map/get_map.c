/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:46:28 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/28 21:42:33 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_surrounded_by_one(char **map)
{
	int	i;
	int	j;
	
	i = 1;
	j = 0;
	while (map[0][j] == '1')
		j++;
	if (!map[0][j])
		return (0);
	j = 0;
	while (map[i + 1])
	{
		if (!(map[i][j] == '1' && map[i][ft_strlen(map[i]) - 1] == '1'))
			return (0);
		i++;
	}
	j = 0;
	while (map[i][j] == '1')
		j++;
	if (!map[i][j])
		return (0);
	return (1);
}

static int is_in_charset(char c)
{
	const char	set[] = "01NSEW";
	char		*s;

	s = set;
	while (s)
	{
		if (c == *s)
			break ;
		s++;
	}
	if (!s)
		return (0);
	return (1);
}

int		check_map(char **map)
{
	int	i;
	int j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_in_charset(map[i][j]))
				return (0);
			j++;
		}
		i++;
		
	}
	if (i < 3)
		return (0);
	return (1);
}

t_map	*get_map(char *file)
{
	return (NULL);
}
