/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:09:54 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/29 13:13:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_type(t_prog *prog, char a)
{
	int	c;

	c = a - 33;
	if (c < 0 || c >= KEYS_MAX)
		return (-1);
	if (prog->map_keys[c])
		return (prog->map_keys[c]->type);
	return (-1);
}

static int	check_char(t_prog *prog, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_in(map[y][x], "WSNE0") && get_type(prog, map[y][x]) == -1 && !is_sprite_key(map[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	one_player(char **map)
{
	int	y;
	int	x;
	int	p;

	p = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_in(map[y][x], "WSEN"))
				p++;
			x++;
		}
		y++;
	}
	return (p == 1);
}

static int	check_surrounded_by_one(t_prog *prog, char **map)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (get_type(prog, map[0][j]) == 'W')
		j++;
	if (map[0][j])
		return (0);
	while (map[i + 1])
	{
		if (!(get_type(prog, map[i][0]) == 'W'
			&& get_type(prog, map[i][ft_strlen(map[i]) - 1]) == 'W'))
			return (0);
		i++;
	}
	j = 0;
	while (get_type(prog, map[i][j]) == 'W')
		j++;
	if (map[i][j])
		return (0);
	return (1);
}

int	check_map(t_prog *prog, char **map)
{
	printf("check_char\n");
	if (!check_char(prog, map))
		return (0);
	printf("one_player\n");
	if (!one_player(map))
		return (0);
	printf("check_surrounded_by_one\n");
	if (!check_surrounded_by_one(prog, map))
		return (0);
	return (1);
}
