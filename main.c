/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:38:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/30 15:07:02 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_prog *prog, t_point a, t_point b)
{
	float	s;
	float	p;
	float	density;

	s = (a.y - b.y) / (a.x - b.x);
	p = a.y - s * a.x;
	if (b.x < a.x)
	{
		b.y = b.x;
		b.x = a.x;
		a.x = b.y;
	}
	density = 0.1;
	while (a.x < b.x)
	{
		a.y = s * a.x + p;
		mlx_img_pixel_put(prog, a.x, a.y, 0xffffff);
		a.x += density;
	}
}

void	draw_line_player(t_prog *prog)
{
	float	angle;
	t_point	a;
	t_point	b;

	angle = prog->player.angle * 0.01;
	a.x = prog->player.x;
	a.y = prog->player.y;
	b.x = prog->player.dx * cosf(angle) + prog->player.x;
	b.x = prog->player.dx * sinf(angle) + prog->player.y;
	draw_line(prog, a, b);
	//printf("%f\n", sqrtf(x*x + y*y));
}

void	draw_square(t_prog *prog, int x, int y, int w, int h, int color)
{
	int	wx;
	int	wy;

	wx = x;
	while (wx < x + w)
	{
		wy = y;
		while (wy < y + h)
		{
			mlx_img_pixel_put(prog, wx, wy, color);		
			wy++;
		}
		wx++;
	}
}

void	init_player_pos(t_prog *prog)
{
	int i;
	int j;
	int w;
	int h;

	w = get_longest_line_width(prog->map->map);
	w = round(WIN_SIZE / w);
	h = ft_arrlen((void **)prog->map->map);
	h = round(WIN_SIZE / h);

	i = 0;
	while (prog->map->map[i]) {
		j = 0;
		while (prog->map->map[i][j]) {
			if (prog->map->map[i][j] == 'N') {
				prog->player.x = (j * w) + j + w/2 - 20/2;
				prog->player.y = (i * h) + i + h/2 - 20/2;
				return ;
			}
			j++;	
		}
		i++;
	}
}

// TODO : Draw Player
void	draw_player(t_prog *prog)
{
	draw_square(prog, prog->player.x, prog->player.y, 20, 20, 0xffff00);	
}

void	draw_map(t_prog *prog)
{
	char	**map;
	int		w;
	int		h;
	int		i;
	int		j;

	map = prog->map->map;
	w = get_longest_line_width(map);
	w = round(WIN_SIZE / w);
	h = ft_arrlen((void **)map);
	h = round(WIN_SIZE / h);
	i = 0;
	while (map[i]) {
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(prog, (j * w) + j, (i * h) + i, w, h, 0xffffff);
			j++;
		}
		i++;
	}
}

void	game_frame(t_prog *prog)
{
	replace_image(prog);
	replace_image(prog);
	draw_map(prog);
	draw_player(prog);
	draw_line_player(prog);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
}

int	start_cub3d(char *file)
{
	t_prog	*prog;

	prog = init_prog();
	if (!init_mlx(prog))
		return (0);
	prog->map = get_map(file);
	init_player_pos(prog);	
	if (!prog || !prog->map)
	{
		printf("Error\n");
		return (0);
	}
	game_frame(prog);
	mlx_hook(prog->win, ON_KEYDOWN, 0, on_key_down, prog);
	mlx_hook(prog->win, ON_KEYUP, 0, on_key_up, prog);
	mlx_hook(prog->win, ON_DESTROY, 0, exit_cube3d, prog);
	mlx_loop(prog->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	if (check_arg(ac, av))
	{
		if (start_cub3d(av[1]))
			return (0);
		return (1);
	}
	return (1);
}
