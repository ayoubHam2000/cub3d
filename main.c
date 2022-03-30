/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:38:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 18:45:42 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_prog *image, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 2200 && y < 1200 && y >= 0)
	{
		dst = image->addr + (y * image->line_length
				+ x * (image->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

t_draw	ft_change(t_draw *draw)
{
	t_draw	temp;

	temp.x0 = draw->x1;
	temp.x1 = draw->x0;
	temp.y0 = draw->y1;
	temp.y1 = draw->y0;
	return (temp);
}

int	ft_isox(int x, int y)
{
	return (x - y);
}

int	ft_isoy(int x, int y, int z)
{
	return ((x + y) / 2 - z);
}

int	ft_abs(int sum)
{
	if (sum < 0)
		return (-sum);
	return (sum);
}

t_draw	*ft_isometri(t_draw *tab, int z0, int z1)
{
	t_draw	*draw;

	draw = malloc(sizeof(t_draw));
	if (!draw)
		return (NULL);
	if (data->translate == 1)
	{
		draw->x0 = tab->x0;
		draw->x1 = tab->x1;
		draw->y0 = tab->y0;
		draw->y1 = tab->y1;
		return (draw);
	}
	draw->x0 = ft_isox(tab->x0, tab->y0);
	draw->x1 = ft_isox(tab->x1, tab->y1);
	draw->y0 = ft_isoy(tab->x0, tab->y0, z0 * data->alt);
	draw->y1 = ft_isoy(tab->x1, tab->y1, z1 * data->alt);
	return (draw);
}

int	start_cub3d(char *file)
{
	t_prog	*prog;

	printf("sdf\n");
	prog = init_prog();
	prog->map = get_map(file);
	if (!prog || !prog->map)
		return (0);
	/*if (!init_mlx(prog))
		return (0);
	mlx_loop(prog->mlx);*/
	return (1);
}
static int	draw_line_down(t_draw draw)
{
	t_prog	*prog;
	draw.dx = draw.x1 - draw.x0;
	draw.dy = draw.y1 - draw.y0;
	draw.next = 1;
	if (draw.dy < 0)
	{
		draw.next = -1;
		draw.dy = -draw.dy;
	}
	draw.index = 2 * draw.dy - draw.dx;
	while (draw.x0 <= draw.x1)
	{
		my_mlx_pixel_put(prog->win, draw.x0, draw.y0, 0Xffffff);
		draw.x0++;
		if (draw.index > 0)
		{
			draw.y0 = draw.y0 + draw.next;
			draw.index = draw.index + 2 * (draw.dy - draw.dx);
		}
		else
			draw.index = draw.index + 2 * draw.dy;
	}
	return (0);
}

static int	draw_line_up(t_draw draw)
{
	t_prog	*prog;
	draw.dx = draw.x1 - draw.x0;
	draw.dy = draw.y1 - draw.y0;
	draw.next = 1;
	if (draw.dx < 0)
	{
		draw.next = -1;
		draw.dx = -draw.dx;
	}
	draw.index = 2 * draw.dx - draw.dy;
	while (draw.y0 <= draw.y1)
	{
		my_mlx_pixel_put(prog->win, draw.x0, draw.y0, 0Xffffff);
		draw.y0++;
		if (draw.index > 0)
		{
			draw.x0 = draw.x0 + draw.next;
			draw.index = draw.index + 2 * (draw.dx - draw.dy);
		}
		else
			draw.index = draw.index + 2 * draw.dx;
	}
	return (0);
}

void	draw_line(t_draw *tab, int z0, int z1)
{
	t_draw	*draw;

	draw = ft_isometri(tab, z0, z1);
	if (ft_abs(draw->y1 - draw->y0) < ft_abs(draw->x1 - draw->x0))
	{
		if (draw->x0 > draw->x1)
			draw_line_down(ft_change(draw));
		else
			draw_line_down(*draw);
	}
	else
	{
		if (draw->y0 > draw->y1)
			draw_line_up(ft_change(draw));
		else
			draw_line_up(*draw);
	}
	free(draw);
}

int	main(int ac, char **av)
{
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("-%d-", ft_strlen(line));
	}
	/*if (check_arg(ac, av))
	{
		if (start_cub3d(av[1]))
			return (0);
		return (1);
	}*/
	return (1);
}
