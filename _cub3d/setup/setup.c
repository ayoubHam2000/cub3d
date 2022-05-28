/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:46:28 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/27 20:10:42 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	setup(t_prog *prog, char *file)
{
	t_file_data	*data;

	data = read_file(file);
	if (!data)
		return (0);
	printf("Load texture\n");
	if (!load_textures(prog, data->texs))
		return (0);
	printf("Load types\n");
	if (!load_types(prog, data->texs, data->types))
		return (0);
	printf("Load map\n");
	if (!load_map(prog, data->map))
		return (0);
	init_player_pos(&prog->player);
	free_all(NULL);
	return (1);
}
