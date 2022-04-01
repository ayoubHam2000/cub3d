/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:31:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/01 17:31:10 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(int x, int y, int length, int color)
{
	int	wx;
	int	wy;

	wx = x + length;
	wy = y + length;
	x++;
	while (x < wx - 1)
	{
		y = wy - length + 1;
		while (y < wy - 1)
		{
			ft_put_pixel(x, y, color);
			y++;
		}
		x++;
	}
}
