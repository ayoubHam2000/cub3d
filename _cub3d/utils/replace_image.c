/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:20:10 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 22:21:17 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*replace_image(t_prog *prog)
{
	if (prog->img.img)
		mlx_destroy_image(prog->mlx, prog->img.img);
	prog->img.img = mlx_new_image(prog->mlx, prog->w_size, prog->w_size);
	prog->img.addr = mlx_get_data_addr(prog->img.img, \
		&(prog->img.bits_per_pixel), \
		&(prog->img.line_length), &(prog->img.endian));
	if (!prog->img.img || !prog->img.addr)
		return (NULL);
	return (prog);
}
