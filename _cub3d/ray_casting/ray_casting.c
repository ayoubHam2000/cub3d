/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:20:23 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/16 20:14:01 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda(t_ray *ray, char **map)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1' || map[ray->map_y][ray->map_x] == '2')
			break ;
	}
	if (ray->side == 0)
		ray->dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->dist = ray->side_dist_y - ray->delta_dist_y;
}

static void	ray_info(t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->wall_x = ray->pos_y + ray->dist * ray->y;
		if (ray->map_x < ray->pos_x)
			ray->side = 2;
		else
			ray->side = 3;
	}
	else
	{
		ray->wall_x = ray->pos_x + ray->dist * ray->x;
		if (ray->map_y < ray->pos_y)
			ray->side = 2;//0
		else
			ray->side = 3;//1
	}
	ray->wall_x = ray->wall_x - (int)ray->wall_x;
	ray->line_height = (HEIGHT/ ray->dist);
}

void	raycasting(double camera_x, t_ray *ray, t_player *player, char **map)
{
	ray->x = player->dir_x + player->plane_x * camera_x;
	ray->y = player->dir_y + player->plane_y * camera_x;
	ray->delta_dist_x = 1e30;
	ray->delta_dist_y = 1e30;
	if (ray->x != 0)
		ray->delta_dist_x = fabs(1.0 / ray->x);
	if (ray->y != 0)
		ray->delta_dist_y = fabs(1.0 / ray->y);
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;

	ray->step_x = (ray->x >= 0) * 2 - 1;
	ray->step_y = (ray->y >= 0) * 2 - 1;
	if (ray->x < 0)
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1 - ray->pos_x) * ray->delta_dist_x;
	if (ray->y < 0)
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1 - ray->pos_y) * ray->delta_dist_y;
	dda(ray, map);
	ray_info(ray);
}
