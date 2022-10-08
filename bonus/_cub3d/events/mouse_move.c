/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:52:38 by aben-ham          #+#    #+#             */
/*   Updated: 2022/09/29 18:28:00 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_mouse_move(int x, int y, t_prog *prog)
{
	prog->old_m_x = prog->m_x;
	prog->m_x = x;
	prog->old_m_y = y;
	//printf("%d\n", y);
	return (0);
}
