/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:46:28 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 16:55:34 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_spaces(char **str)
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

static int is_in_charset(char c, int *p)
{
	const char	set[] = "01NSEW";
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
	if (*p >= 2)
		return (0);
	return (1);
}

int		check_map(char **map)
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
	if (i < 3)
		return (0);
	return (1);
}

static int	msk_type_split(char c)
{
	static int	flag;

	if (c == 0)
	{
		flag = 0;
		return (0);
	}
	if (c == ' ' && !flag)
		flag = 1;
	else if (c != ' ' && flag)
		flag = 2;
	if (flag == 2 || !flag)
		return (0);
	return (1);
}

int		is_a_valide_type(char *type, char *stype)
{
	int	i;

	i =  ft_strlen(stype);
	if (ft_strncmp(type, stype, i) == 0)
	{
		while (type[i] == ' ')
			i++;
		if (!type[i])
			return (0);
		else
			return (1);
	}
	return (0);
}

char	*get_types_data(int fd)
{
	const char	stypes[][2] = {"NO", "SO", "WE", "EA", "F", "C"};
	char		**res;
	char		*line;
	int			i;

	res = s_malloc(sizeof(char *) * 7);
	line = get_next_line(fd);
	i = 0;
	while (line && i < 6)
	{
		if (!(line[0] == '\n' && !line[1]))
		{
			if (is_a_valide_type(line, stypes[i]))
				res[i] = line;
			else
				break ;
			i++;
		}
		line = get_next_line(fd);
	}
	res[i] = NULL;
	if (i == 6)
		return (res);
	return (free_all(NULL));
}

int		get_type_index(char *type)
{
	const char	stypes[][2] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;

	i = 0;
	while (stypes[i])
	{
		if (ft_strcmp(type,stypes[i]))
			return (i);
		i++;
	}
	return (0);
}

t_type	**get_types(int	fd)
{
	char	**types;
	char	**info;
	t_type	**res;
	int		i;

	res = ft_malloc(sizeof(t_type *) * 7);
	types = get_types_data(fd);
	if (types[i])
	{
		info = msk_split(types[i], msk_type_split);
		res[i] = ft_malloc(sizeof(t_type));
		res[i]->id = get_type_index(info[0]);
		res[i]->data = info[1];
		ft_addrs_exclude(info[1]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**get_map_data(int fd)
{
	t_queue	*queue;
	char *line;
	
	queue = q_init();
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != 0 || line[1] != '\n')
			q_enqueue(queue, line);
		line = get_next_line(fd);
	}
}

t_map	*get_map(char *file)
{
	int		fd;
	char	*line;
	t_map	*map;

	map = ft_malloc(sizeof(t_map));
	map->map = NULL;
	map->types = NULL;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		line =
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}
