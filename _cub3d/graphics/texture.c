/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 09:24:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/18 15:32:52 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define PNG 0
#define XPM 1

static int	tex_extension(char *str)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (ft_strcmp(ext, ".png"))
		return (PNG);
	else if (ft_strcmp(ext, ".xpm"))
		return (XPM);
	return (-1);
}

void	*get_texture(t_prog *prog, void *path)
{
	t_tex	*img;
	int		ext;

	ext = tex_extension(path);
	if (ext == -1)
		return (NULL);
	img = ft_malloc(sizeof(t_tex));
	if (ext == XPM)
		img->tex = mlx_xpm_file_to_image(prog->mlx, path, &img->width, &img->height);
	else
		img->tex = mlx_png_file_to_image(prog->mlx, path, &img->width, &img->height);
	if (!(img->tex))
		return (NULL);
	img->ptr = mlx_get_data_addr(img->tex, &img->bpp, &img->size_line, &img->endian);
	if (!(img->ptr))
		return (NULL);
	return (img);
}

int	load_textures(t_prog *prog, t_queue *texs)
{
	int		i;
	t_node	*node;

	if (texs->len >= TEX_BUFFER_SIZE)
		return (0);
	i = 0;
	node = texs->first;
	while (i < texs->len)
	{
		printf("load %s\n", node->p);
		prog->texs[i] = get_texture(prog, node->p);
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
		node = node->next;
	}
	return (1);
}

int	get_tex_color(t_tex *tex, int x, int y)
{
	if (x >= 0 && x < tex->width && y >= 0 && y < tex->height)
	{
		return (*((int *)(tex->ptr) + (\
			(tex->width * y) + (x) \
			)));
	}
	return (0);
}
