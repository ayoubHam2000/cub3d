/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:41:51 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/18 15:24:44 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_queue	*read_section(int fd, char *line)
{
	t_queue	*res;
	int		len;
	char	*line;

	len = ft_atoi(line);
	if (len <= 0)
		return (NULL);
	res = q_init();
	while (len > 0)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		if (!is_empty_line(line) && !is_comment(line))
		{
			q_enqueue(res, line);
			len--;
		}
	}
	return (res);
}

t_queue	*read_map_data(t_queue *data, int fd, char *line)
{
	t_queue	*res;
	char	*line;

	res = q_init();
	while (line)
	{
		if (is_comment(line))
			return (NULL);
		if (!is_empty_line(line))
			q_enqueue(res, line);
		line = get_next_line(fd);
	}
	return (res);	
}

t_file_data	*get_file_data(int fd)
{
	t_file_data	*data;
	char		*line;
	int			state;

	data = s_malloc(sizeof(t_file_data));
	line = get_next_line(fd);
	state = 0;
	while (line)	
	{
		if (!is_empty_line(line) && is_comment(line))
		{
			if (state == 0)
				data->texs = read_section(fd, line);
			else if (data->texs && state == 1)
				data->types = read_section(fd, line);
			else if (data->texs && data->types)
				return (read_map_data(data, fd, line));
			else
				return (NULL);
			state++;
		}
		line = get_next_line(fd);
	}
	return (data);
}
