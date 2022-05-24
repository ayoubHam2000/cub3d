/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:24:55 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/22 11:24:38 by mbel-bas         ###   ########.fr       */
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

//==================

int	*get_tex(int x, int y)
{
	char	c;

	c = get_prog()->player.map_info[y][x].key - 33;
	return (get_prog()->map_keys[c]->tex_index);
}


//==================


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
