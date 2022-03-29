/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:38:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 22:31:40 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_cub3d(char *file)
{
	t_prog	*prog;

	prog = init_prog();
	prog->map = get_map(file);
	if (!prog || !prog->map)
	{
		printf("Error\n");
		return (0);
	}
	if (!init_mlx(prog))
		return (0);
	replace_image(prog);
	mlx_img_pixel_put(prog, 5, 5, 0xffffff);
	mlx_img_pixel_put(prog, 5, 6, 0xffffff);
	mlx_img_pixel_put(prog, 6, 5, 0xffffff);
	mlx_img_pixel_put(prog, 6, 5, 0xffffff);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
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
