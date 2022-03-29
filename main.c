/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:38:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 14:08:34 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
