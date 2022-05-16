void	game(t_prog *prog)
{
	int			w, h;
	int			x;
	t_pointf	ray;
	t_pointf	deltaDist;
	t_pointf	sideDist;
	t_point		map_pos;
	t_point		step;
	t_pointf	pos;
	double		cameraX;
	double		perpWallDist;
	int			hit;
	int			side; //was a NS or a EW wall hit?
	int			lineHeight;
	double		wall_x;
	t_tex		*tex;
	static int f = 0;
	static size_t start_time;
	size_t		s;

	s = get_time();
	replace_image(prog, WIN_SIZE, WIN_SIZE);
	w = WIN_SIZE;
	h = WIN_SIZE;
	x = 0;
	
	pos.x = prog->player.x;
	pos.y = prog->player.y;
	while (x < w)
	{
		cameraX = 2 * x / (double)w - 1.0;
		ray.x = prog->player.dir_x + prog->player.plane_x * cameraX;
		ray.y = prog->player.dir_y + prog->player.plane_y * cameraX;

		deltaDist.x = (ray.x == 0) ? 1e30 : fabs(1.0 / ray.x);
		deltaDist.y = (ray.y == 0) ? 1e30 : fabs(1.0 / ray.y);

		map_pos.x = (int)pos.x;
		map_pos.y = (int)pos.y;

		if (ray.x < 0)
		{
			step.x = -1;
			sideDist.x = (pos.x - map_pos.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (map_pos.x + 1 - pos.x) * deltaDist.x;
		}
		if (ray.y < 0)
		{
			step.y = -1;
			sideDist.y = (pos.y - map_pos.y) * deltaDist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (map_pos.y + 1 - pos.y) * deltaDist.y;
		}
		hit = 0;
		while (!hit)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				map_pos.x += step.x;
				side = 0;
			}
			else
			{
				sideDist.y += deltaDist.y;
				map_pos.y += step.y;
				side = 1;
			}
			if (is_hit_a_tile(prog->map, map_pos.x, map_pos.y))
				hit = 1;
		}
		if (side == 0)
			perpWallDist = sideDist.x - deltaDist.x;
		else
			perpWallDist = sideDist.y - deltaDist.y;
		
		lineHeight = (h / perpWallDist);
		//texture--------------------------
		//texture--------------------------
		if (side == 0)
		{
			wall_x = pos.y + perpWallDist * ray.y;
			if (map_pos.x < pos.x)
				tex = prog->texs[0];
			else
				tex = prog->texs[1];
		}
		else
		{
			wall_x = pos.x + perpWallDist * ray.x;
			if (map_pos.y < pos.y)
				tex = prog->texs[2];
			else
				tex = prog->texs[3];
		}
		wall_x = wall_x - (int)wall_x;
		draw_tex_line(tex, wall_x, lineHeight, perpWallDist, x);
		x++;
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
	printf("--->%lu\n", get_time() - s);
}



**



void	game(t_prog *prog)
{
	t_ray		ray;
	int			x;
	double		cameraX;
	int			lineHeight;
	t_tex		*tex;
	
	static int f = 0;
	static size_t start_time;
	size_t		s;

	s = get_time();
	replace_image(prog, WIN_SIZE, WIN_SIZE);
	x = 0;
	
	ray.pos_x = prog->player.x;
	ray.pos_y = prog->player.y;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1.0;
		ray.x = prog->player.dir_x + prog->player.plane_x * cameraX;
		ray.y = prog->player.dir_y + prog->player.plane_y * cameraX;

		ray.delta_dist_x = (ray.x == 0) ? 1e30 : fabs(1.0 / ray.x);
		ray.delta_dist_y = (ray.y == 0) ? 1e30 : fabs(1.0 / ray.y);

		ray.map_x = (int)ray.pos_x;
		ray.map_y = (int)ray.pos_y;

		if (ray.x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (ray.pos_x - ray.map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1 - ray.pos_x) * ray.delta_dist_x;
		}
		if (ray.y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (ray.pos_y - ray.map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1 - ray.pos_y) * ray.delta_dist_y;
		}
		while (1)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}
			if (is_hit_a_tile(prog->map, ray.map_x, ray.map_y))
				break ;
		}
		if (ray.side == 0)
			ray.dist = ray.side_dist_x - ray.delta_dist_x;
		else
			ray.dist = ray.side_dist_y - ray.delta_dist_y;
		
		lineHeight = (HEIGHT / ray.dist);
		//texture--------------------------
		//texture--------------------------
		if (ray.side == 0)
		{
			ray.wall_x = ray.pos_y + ray.dist * ray.y;
			if (ray.map_x < ray.pos_x)
				tex = prog->texs[0];
			else
				tex = prog->texs[1];
		}
		else
		{
			ray.wall_x = ray.pos_x + ray.dist * ray.x;
			if (ray.map_y < ray.pos_y)
				tex = prog->texs[2];
			else
				tex = prog->texs[3];
		}
		ray.wall_x = ray.wall_x - (int)ray.wall_x;
		draw_tex_line(tex, ray.wall_x, lineHeight, ray.dist, x);
		x++;
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
	printf("--->%lu\n", get_time() - s);
}







static void	rotate_mouse(t_prog *prog)
{
	double		oldDirX;
	double		oldPlaneX;
	t_player	*p;
	double		d;
	static int huh;

	if (huh == prog->m_x)
		return ;
	p = &prog->player;
	oldDirX = p->dir_x;
	d = (prog->old_m_x - prog->m_x) * 0.17;
	p->dir_x = p->dir_x  * cos(R_SPEED * d) - p->dir_y * sin(R_SPEED * d);
	p->dir_y = oldDirX * sin(R_SPEED * d) + p->dir_y * cos(R_SPEED * d);
	oldPlaneX = p->plane_x;
	p->plane_x = p->plane_x * cos(R_SPEED * d) - p->plane_y * sin(R_SPEED * d);
	p->plane_y = oldPlaneX * sin(R_SPEED * d) + p->plane_y * cos(R_SPEED * d);
	huh = prog->m_x;
}