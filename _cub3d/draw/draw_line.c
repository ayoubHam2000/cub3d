/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:31:16 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/01 17:31:24 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(float angle, float length, float offsetx, float offsety, float color)
{
	float	r;
	float	x;
	float	y;

	r = 0.f;
	length = fmin(length, MAX_LINE);
	while (r < length)
	{
		x = r * cosf(angle);
		y = r * sinf(angle);
		ft_put_pixel(x + offsetx, y + offsety, color);
		r += 0.1f;
	}
}
