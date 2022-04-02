/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:49:58 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 21:59:21 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(int x, int y, int w, int h)
{
	int	wx;
	int	wy;
	int	c;

	wx = x + w;
	wy = y + h;
	c = get_prog()->color;
	while (x < wx)
	{
		y = wy - h;
		while (y < wy)
		{
			ft_put_pixel(x, y, c);
			y++;
		}
		x++;
	}
}
