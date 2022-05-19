/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:24:55 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/19 15:40:34 by aben-ham         ###   ########.fr       */
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
	if (ft_in(c, "NSWE0"))
		return (0);
	return (get_prog()->map_keys[c - 33]->type);
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
