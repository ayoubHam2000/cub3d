/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:08:17 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/21 16:11:11 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	remove_spaces(char **str)
{
	int	count;
	int	i;
	int	j;
	
	i = 0;
	while (str[i])
	{
		j = 0;
		count = 0;
		while (str[i][j])
		{
			if (str[i][j] != ' ')
				str[i][count++] = str[i][j];
			j++;
		}
		str[i][count] = '\0';
		i++;
	}
}

static char	**get_map_matrix(t_queue *map)
{
	char	**data;
	char	**res;
	int		i;

	if (map->len < 3L)
		return (0);
	data = s_malloc(sizeof(char *) * (map->len + 1));
	i = 0;
	while (1)
	{
		data[i] = q_dequeue(map);
		if (!data[i])
			break ;
		i++;
	}
	remove_spaces(data);
	return (data);
}

void	construct_map_data(t_prog *prog, char **map)
{
	int			x;
	int			y;
	t_m_info	**map_info;

	map_info = ft_malloc(sizeof(t_m_info *) * (ft_arrlen(map) + 1));
	y = -1;
	while (map[y])
	{
		map_info[y] = ft_malloc(sizeof(t_m_info) * (ft_strlen(map[y])));
		x = -1;
		while (map[y][x])
		{
			map_info[y][x].key = map[y][x];
			map_info[y][x].type = map[y][x];
			map_info[y][x].timer = 0.0f;
			map_info[y][x].step = 0;
			if (map[y][x] != '0')
				map[y][x] = '1';
			x++;
		}
		ft_addrs_exclude(map[y]);
		y++;
	}
	map_info[y] = NULL;
	prog->player.map = map;
	prog->player.map_info = map_info;
}

int	load_map(t_prog *prog, t_queue *map)
{
	char	**data;

	data = get_map_matrix(map);
	if (!data)
		return (0);
	if (!check_map(prog, data))
		return (0);
	construct_map_data(prog, data);
	return (1);
}
