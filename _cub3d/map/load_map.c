/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:08:17 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/19 15:34:41 by aben-ham         ###   ########.fr       */
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

char	**load_map(t_prog *prog, t_queue *map)
{
	char	**data;
	int		i;

	data = get_map_matrix(map);
	if (!data)
		return (NULL);
	if (!check_map(prog, data))
		return (NULL);
	i = 0;
	printf("%p\n", data);
	while (data[i])
	{
		printf("%s\n", data[i]);
		ft_addrs_exclude(data[i++]);
	}
	ft_addrs_exclude(data);
	prog->player.map = data;
	return (data);
}
