/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:20:23 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/24 14:43:13 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	stop(t_ray *ray, t_player *player)
{
	if (player->map_info[ray->map_y][ray->map_x].type == 'D')
	{
		ray->hit_door = 1;
		ray->door_x = ray->map_x;
		ray->door_y = ray->map_y;
		ray->door_side = ray->side;
		if (ray->side == 0)
			ray->door_dist = ray->side_dist_x - ray->delta_dist_x;
		else
			ray->door_dist = ray->side_dist_y - ray->delta_dist_y;
		if (ray->side == 0)
			ray->door_wall_x = ray->pos_y + ray->dist * ray->y;
		else
			ray->door_wall_x = ray->pos_x + ray->dist * ray->x;
		ray->door_wall_x = ray->door_wall_x - (int)ray->door_wall_x;
		if (ray->door_wall_x < 0.5)
			return (0);
		return (1);
	}
	else if (player->map_info[ray->map_y][ray->map_x].type == 'S')
		
		return (0);
	if (player->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

static void	dda(t_ray *ray, t_player *player)
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
		if (stop(ray, player))
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
			ray->side = WE;
		else
			ray->side = EA;
	}
	else
	{
		ray->wall_x = ray->pos_x + ray->dist * ray->x;
		if (ray->map_y < ray->pos_y)
			ray->side = NO;
		else
			ray->side = SO;
	}
	ray->wall_x = ray->wall_x - (int)ray->wall_x;
	ray->line_height = (HEIGHT / ray->dist);
}

void	raycasting(double camera_x, t_ray *ray, t_player *player)
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
	ray->hit_door = 0;
	dda(ray, player);
	ray_info(ray);
}
