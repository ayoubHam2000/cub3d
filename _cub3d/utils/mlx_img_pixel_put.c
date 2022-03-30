/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_pixel_put.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:17:45 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/30 10:33:39 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_img_pixel_put(t_prog *prog, int x, int y, int color)
{
	char	*dst;

	if (y >= prog->w_size || x >= prog->w_size || y < 0 || x < 0)
		return ;
	dst = prog->img.addr + (y * prog->img.line_length \
		+ x * (prog->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
