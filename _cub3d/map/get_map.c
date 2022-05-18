/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:46:28 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/18 15:41:38 by aben-ham         ###   ########.fr       */
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

int	setup_keys(t_prog *prog, t_queue *types)
{
	t_node	*node;
	t_type	*type;
	char	**textures;
	int		i;
	int		len;

	if (!types)
		return (0);
	textures = ft_split(types->first->p, ' ');
	if (ft_arrlen(textures) != 2)
		return (0);
	load_textures(prog, textures, 2);
	printf("start 2\n");
	node = types->first->next;
	i = 2;
	while (node)
	{
		type = node->p;
		printf("%d\n", type->id);
		prog->map_keys[type->id] = ft_malloc(sizeof(t_m_key));
		prog->map_keys[type->id]->type = type->type;
		prog->map_keys[type->id]->tex_s = i;
		textures = ft_split(type->data, ' ');
		len = ft_arrlen(textures);
		if (!load_textures(prog, textures, len))
			return (0);
		i += len;
		prog->map_keys[type->id]->tex_e = i;
		node = node->next;
	}
	return (1);
}

int	load_types(t_prog *prog, t_queue *types)
{
	t_node	*node;

	node = 
	while ()
	{
		node = node->next;
	}
}

int	setup(t_prog *prog, char *file)
{
	int			fd;
	t_file_data	*file_data;

	fd = open(file, O_RDONLY);
	file_data = get_file_data(fd);
	if (!file_data)
		return (0);
	if (!load_textures(prog, file_data->texs))
		return (0);
	load_types(prog, file_data->types);
	free_all(NULL);
	return (0);
}

t_map	*get_map(char *file)
{
	int		fd;
	t_map	*map;

	//map = ft_malloc(sizeof(t_map));
	//fd = open(file, O_RDONLY);
	//map->types = get_types(fd);
	/*map->map = get_map_matrix(fd);
	if (!map->types || !map->map)
	{
		free_map(map);
		close(fd);
		return (free_all(NULL));
	}
	map->len = ft_arrlen((void **)map->map);*/
	close(fd);
	return (map);
}
