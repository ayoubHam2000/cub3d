/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:49:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/06/04 14:04:30 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_sprite_key(char c)
{
	return (ft_in(c, "emhb"));
}

int	ft_rand(void)
{
	static int	x;

	x = (1103515245 * x + 12345) % 0x7fffffff;
	return (x & 0x7fffffff);
}

void	play_sound_die(void)
{
	int	i;

	if (!fork())
	{
		i = ft_rand() % 2;
		if (i == 0)
			system("afplay ./resources/static/music/die_1.m4a");
		else if (i == 1)
			system("afplay ./resources/static/music/die_2.m4a");
		exit(1);
	}
}

void	play_sound_door(void)
{
	//int	i;

	if (!fork())
	{
		//i = ft_rand() % 1;
		//if (i == 0)
			system("afplay ./resources/static/music/door_2.mp3");
		//else if (i == 1)
		//	system("afplay ./resources/static/music/die_2.m4a");
		exit(1);
	}
}

void	play_sound_hit(void)
{
	//int	i;

	if (!fork())
	{
		//i = ft_rand() % 1;
		//if (i == 0)
			system("afplay ./resources/static/music/hit_1.mp3");
		//else if (i == 1)
		//	system("afplay ./resources/static/music/die_2.m4a");
		exit(1);
	}
}

void	play_sound_music(void)
{

	if (!fork())
	{
		while (1)
		{
			system("afplay ./resources/static/music/music_1.mp3");
			system("afplay ./resources/static/music/music_2.mp3");
			system("afplay ./resources/static/music/music_3.mp3");
		}
	}
}

void	play_sound_gun(void)
{
	int	i;

	i = fork();
	if (!i)
	{
		system("afplay ./resources/static/music/gun_shot.mp3");
		printf("%d\n", i);
		kill(getpid(), 9);
		exit(0);
	}
}
