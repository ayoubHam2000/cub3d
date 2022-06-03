/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 09:43:16 by aben-ham          #+#    #+#             */
/*   Updated: 2022/06/03 20:45:21 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	shade_color(int color, float divide)
{
	if (divide <= 1.)
		return (color);
	return (((int)(((0xFF0000 & color) >> 16) / divide) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / divide) << 8)
		+ ((int)((0x0000FF & color) / divide)));
}

int	get_tex_color(t_tex *tex, int x, int y)
{
	if (x >= 0 && x < tex->width && y >= 0 && y < tex->height)
	{
		return (*((int *)(tex->ptr) + (\
			(tex->width * y) + (x) \
			)));
	}
	return (0);
}

int	tr_c(int c, int h, int k, int f)
{
	int	r;
	int	g;
	int	b;

	if (h > 0 && (k == 'e' || k == 'm') && f % 4 == 0)
	{
		r = ((c >> 16) & 255) * 0.6 + 255 * 0.4;
		g = ((c >> 8) & 255) * 0.6 + 255 * 0.4;
		b = (c & 255) * 0.6 + 255 * 0.4;
		return (r << 16 | g << 8 | b);
	}
	return (c);
}
