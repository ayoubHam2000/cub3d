/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:24:55 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/21 14:47:12 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *line)
{
	if (!line[0] || (line[0] == '\n' && !line[1]))
		return (1);
	return (0);
}

int	is_comment(char *line)
{
	if (*line == '#')
		return (1);
	return (0);
}

char	get_key_type(char c)
{
	if (c < 0)
		c *= -1;
	if (ft_in(c, "NSWE0"))
		return (0);
	return (get_prog()->map_keys[c - 33]->type);
}

t_m_key	*get_key(char c)
{
	if (c < 0)
		c *= -1;
	return (get_prog()->map_keys[c - 33]);
}

int	is_tile(char **map, int x, int y)
{
	t_m_key	*k;
	int		c;

	c = map[y][x];
	if (c < 0)
		c *= -1;
	k = get_prog()->map_keys[c - 33];
	if (k && (k->type == 'W' || (k->type == 'D' && map[y][x] > 0)))
		return (1);
	return (0);
}

int	is_block(char **map, int x, int y, int flag)
{
	t_m_key	*k;
	int		c;

	c = map[y][x];
	if (c < 0)
		c *= -1;
	k = get_prog()->map_keys[c - 33];
	if (flag && k)
	{
		if (k->type == 'W' || (k->type == 'D' && map[y][x] > 0))
			return (1);
	}
	else if (k)
	{
		if (k->type == 'W' || (k->type == 'D'))
			return (1);
	}
	return (0);
}

int	get_longest_line_width(char **map)
{
	int	i;
	int	max;
	
	max = 0;
	i = 0;
	while (map[i])
	{
		if (max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}
