/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:46:28 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/31 21:17:33 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->types)
	{
		while (map->types[i])
		{
			free(map->types[i]->data);
			free(map->types[i++]);
		}
		free(map->types);
	}
	i = 0;
	if (map->map)
	{
		while (map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
	free(map);
}

t_map	*get_map(char *file)
{
	int		fd;
	t_map	*map;

	map = ft_malloc(sizeof(t_map));
	fd = open(file, O_RDONLY);
	map->types = get_types(fd);
	map->map = get_map_matrix(fd);
	if (!map->types || !map->map)
	{
		free_map(map);
		close(fd);
		return (free_all(NULL));
	}
	map->len = ft_arrlen((void **)map->map);
	close(fd);
	return (map);
}
