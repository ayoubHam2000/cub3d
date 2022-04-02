/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:53:47 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 21:56:56 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel_color(int x, int y)
{
	static t_prog	*prog;
	char	*dst;

	if (!prog)
		prog = get_prog();
	if (y >= prog->img.img_h || x >= prog->img.img_w || y < 0 || x < 0)
		return ;
	dst = prog->img.addr + (y * prog->img.line_length \
		+ x * (prog->img.bits_per_pixel / 8));
	*(unsigned int *)dst = prog->color;
}
