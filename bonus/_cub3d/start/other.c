/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:49:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/08/22 09:49:49 by aben-ham         ###   ########.fr       */
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
	system("afplay ./resources/static/music/die_1.m4a &");
}

void	play_sound_door(void)
{
	system("afplay ./resources/static/music/door_2.mp3 &");
}

void	play_sound_hit(void)
{
	system("afplay ./resources/static/music/hit_1.mp3 &");
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
	//write(1, "\a", 1);
	system("afplay ./resources/static/music/gun_shot.mp3 &");
}
