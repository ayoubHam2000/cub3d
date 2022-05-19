void	my_floor(t_prog *prog)
{
	int	x;
	int	y;
	double	dist;
	double	floor_x;
	double	floor_y;
	double	step_x;
	double	step_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	t_tex	*ceil_tex;
	t_tex	*floor_tex;
	int		color;

	ceil_tex = prog->texs[0];
	floor_tex = prog->texs[1];
	y = 0;
	while (y < HEIGHT)
	{
		double m_p = HEIGHT - prog->m_y;
		dist = (HEIGHT * 0.5) / (y - m_p);
		floor_x = prog->player.x + dist * (prog->player.dir_x - prog->player.plane_x);
		floor_y = prog->player.y + dist * (prog->player.dir_y - prog->player.plane_y);
		step_x = dist * (2 * prog->player.plane_x) / WIDTH;
		step_y = dist * (2 * prog->player.plane_y) / WIDTH;
		x = 0;
		while (x < WIDTH)
		{
			cell_x = (int)floor_x;
			cell_y = (int)floor_y;
			tx = (int)(ceil_tex->width * (floor_x - cell_x)) & (ceil_tex->width -1);
			ty = (int)(ceil_tex->height * (floor_y - cell_y)) & (ceil_tex->height -1);
			
		
			if (y > m_p)
			{
				color = get_tex_color(ceil_tex, tx, ty);
				color = (color >> 1) & 8355711;
				ft_put_pixel(x, y, color);
			}
			floor_x += step_x;
			floor_y += step_y;
			x++;
		}
		y++;
	}
}