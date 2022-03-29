/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:22:54 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 22:04:37 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	get_type_index(const char type[2])
{
	const char	stypes[][3] = {"NO\0", "SO\0", "WE\0", "EA\0", "F\0", "C\0"};
	int			i;

	i = 0;
	while (stypes[i])
	{
		if (!ft_strncmp(type, stypes[i], ft_strlen(stypes[i])))
			return (i);
		i++;
	}
	return (0);
}

static int	is_a_valide_type(char *type, const char stype[2])
{
	int	i;

	i = ft_strlen(stype);
	if (!ft_strncmp(type, stype, i))
	{
		while (type[i] == ' ')
			i++;
		if (!type[i])
			return (0);
		type = remove_break_line(type);
		if (!check_identifier(type + i, get_type_index(stype)))
			return (0);
		else
			return (1);
	}
	return (0);
}

static char	**get_types_data(int fd)
{
	const char	stypes[][3] = {"NO\0", "SO\0", "WE\0", "EA\0", "F\0", "C\0"};
	char		**res;
	char		*line;
	int			i;

	res = s_malloc(sizeof(char *) * 7);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (!is_empty_line(line))
		{
			if (is_a_valide_type(line, stypes[i]))
				res[i] = line;
			else
				break ;
			if (++i == 6)
				break ;
		}
		line = get_next_line(fd);
	}
	res[i] = NULL;
	if (i == 6)
		return (res);
	return (NULL);
}

t_type	**get_types(int	fd)
{
	char	**types;
	char	**info;
	t_type	**res;
	int		i;

	types = get_types_data(fd);
	if (!types)
		return (NULL);
	i = 0;
	res = ft_malloc(sizeof(t_type *) * 7);
	while (types[i])
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
