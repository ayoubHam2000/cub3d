/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:33:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/30 12:59:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# define UBUNTO
# ifdef UBUNTO
# define KEY_L 65363
# define KEY_R 65361
# define KEY_A 97
# define KEY_D 100
# define KEY_W 119
# define KEY_S 115
# define KEY_ESC 65307
# endif

# ifndef UBUNTO
# define KEY_L 123
# define KEY_R 124
# define KEY_A 0
# define KEY_D 2
# define KEY_W 13
# define KEY_S 1
# define KEY_ESC 53
# endif

# define WIN_TITLE "cub3d"
# define WIN_SIZE 500

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

#endif
