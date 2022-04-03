/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 09:24:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/03 10:30:27 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*get_texture(t_prog *prog, void *path)
{
	t_tex	*xpm;
	
	xpm = ft_malloc(sizeof(t_tex));
	xpm->tex = mlx_xpm_file_to_image(prog->mlx, path, &xpm->width, &xpm->height);
	if (!(xpm->tex))
		return (NULL);
	xpm->ptr = mlx_get_data_addr(xpm->tex, &xpm->bpp, &xpm->size_line, &xpm->endian);
	if (!(xpm->ptr))
		return (NULL);
	return (xpm);
}

int	load_textures(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < TEX_NBR)
	{
		prog->texs[i] = get_texture(prog, prog->map->types[i]->data);
		if (!prog->texs[i])
		{
			while (--i >= 0)
			{
				mlx_destroy_image(prog->mlx, prog->texs[i]->tex);
				free(prog->texs[i]);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int		get_tex_color(t_tex *tex, int x, int y)
{
	if (x >= 0 && x < tex->width && y >= 0 && y < tex->height)
	{
		return (*((int *)(tex->ptr) + (\
			(tex->width * y) + (x)\
			)));
	}
	return (0);
}

