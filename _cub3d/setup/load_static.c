/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_static.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 09:46:08 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/28 11:51:10 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**queue_to_arr(t_queue *queue)
{
	char	**arr;
	char	*str;
	size_t	i;

	arr = ft_malloc(sizeof(queue->len) * (sizeof(char *) + 1));
	i = 0;
	while (1)
	{
		str = q_dequeue(queue);
		if (!str)
			break ;
		arr[i] = str;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static char	**load_config(void)
{
	int		fd;
	t_queue	*queue;
	char	*line;

	fd = open("resources/static/config.conf", O_RDONLY);
	if (fd == -1)
		return (NULL);
	queue = q_init();
	line = get_next_line(fd);
	while (line)
	{
		line = ft_strtrim(line, " \n");
		if (!is_empty_line(line))
			q_enqueue(queue, line);
		line = get_next_line(fd);
	}
	return (queue_to_arr(queue));
}

static void	*load_tex_to(t_prog *prog, t_tex *tex[], char **path, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%s\n", path[i]);
		tex[i] = get_texture(prog, path[i]);
		if (!tex[i])
		{
			while (--i >= 0)
			{
				mlx_destroy_image(prog->mlx, tex[i]);
				free(tex[i]);
			}	
			return (path);
		}
		i++;
	}
	return (path + i);
}

int	load_static(t_prog	*prog)
{
	char	**path;

	path = load_config();
	path = load_tex_to(prog, prog->static_tex.gun, path, 5);
	path = load_tex_to(prog, prog->static_tex.game_over, path, 2);
	return (path && path[0] == NULL);
}
