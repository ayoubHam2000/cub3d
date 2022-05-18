/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:24:55 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/18 15:15:37 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*remove_break_line(char *str)
{
	char	*break_line;

	break_line = ft_strchr(str, '\n');
	if (break_line)
		break_line[0] = 0;
	return (str);
}

int	is_blank(char c)
{
	if (c == ' ' || c == '\f' || c == '\t')
		return (1);
	return (0);
}

int	is_empty_line(char *line)
{
	if (!line[0] || (line[0] == '\n' && !line[1]))
		return (1);
	return (0);
}

int	is_comment(char *line)
{
	while (*line && is_blank(*line))
		line++;
	if (*line == '#')
		return (1);
	return (0);
}

int	nb_blank(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_blank(line[i]))
		i++;
	return (i);
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
