/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:08:17 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 22:05:53 by aben-ham         ###   ########.fr       */
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

static char	**get_map_data(int fd)
{
	t_queue	*queue;
	char	*line;
	char	**res;
	int		i;
	
	queue = q_init();
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
			q_enqueue(queue, line);
		line = get_next_line(fd);
	}
	res = ft_malloc(sizeof(char *) * (queue->len + 1));
	i = 0;
	line = q_dequeue(queue);
	while (line)
	{
		res[i++] = remove_break_line(line);
		ft_addrs_exclude(line);
		line = q_dequeue(queue);
	}
	res[i] = NULL;
	remove_spaces(res);
	return (res);
}

char	**get_map_matrix(int fd)
{
	char	**data;
	int		i;

	data = get_map_data(fd);
	if (!data)
		return (NULL);
	if (!check_map(data))
	{
		i = 0;
		while (data[i])
			free(data[i++]);
		free(data);
		return (NULL);
	}
	return (data);
}
