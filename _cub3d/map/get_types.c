/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:22:54 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/18 13:57:38 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	type_msk_split(char c)
{
	static short	counter;

	if (!c)
	{
		counter = 0;
		return (0);
	}
	if (c != ' ')
		counter++;
	if (c != ' ' && counter < 3)
		return (0);
	if (c == ' ' && counter < 3)
		return (1);
	return (0);
}

static t_type *get_type(char *line)
{
	t_type	*type;
	char	**sp;

	sp = msk_split(line, type_msk_split);
	if (ft_arrlen(sp) == 3)
	{
		type = s_malloc(sizeof(t_type));
		type->type = sp[0][0];
		type->id = sp[1][0];
		type->data = sp[2];
		if (!type->data || !ft_in(type->type, "FWDS") || \
		ft_in(type->id, "NSWE0") || type->id < 33 || type->id >= 127)
			return (NULL);
		type->id = sp[1][0] - 33;
	}
	else
		return (NULL);
	return (type);
}

static int	get_nb_type(int fd)
{
	char	*line;
	int		res;

	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line) && !is_comment(line))
		{
			res = ft_atoi(line);
			if (res <= 0)
				return (-1);
			else
				return (res);
		}
		line = get_next_line(fd);
	}
	return (-1);
}

static t_queue	*get_file_types(int fd)
{
	t_queue	*queue;
	char	*line;
	int		nb_type;

	nb_type = get_nb_type(fd);
	if (nb_type == -1)
		return (NULL);
	queue = q_init();
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line) && !is_comment(line))
		{
			q_enqueue(queue, line);
			if (--nb_type <= 0)
				break ;
		}
		line = get_next_line(fd);
	}
	return (queue);
}

t_queue *get_types(t_prog *prog, int fd)
{
	t_queue	*queue;
	t_node	*node;

	queue = get_file_types(fd);
	if (!queue && !queue->first)
		return (NULL);
	node = queue->first->next;
	while (node)
	{
		node->p = get_type(node->p);
		if (!node->p)
			return (NULL);
		node = node->next;
	}
	return (queue);
}
