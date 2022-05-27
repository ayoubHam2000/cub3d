/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:02:22 by mbel-bas          #+#    #+#             */
/*   Updated: 2022/05/27 18:56:10 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void quicksort(int number[25],int first,int last){
   int i, j, pivot, temp;
   if(first<last){
      pivot=first;
      i=first;
      j=last;
      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
         i++;
         while(number[j]>number[pivot])
         j--;
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }
      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);
   }
}

void get_position(int x, int y)
{
	t_sprite sprite[S_NUMBER];
	static int	i;

	i = 0;
	if (i < S_NUMBER)
	{
		sprite[i].x = x + 0.5;
		sprite[i].y = y + 0.5;
		i++;
	}
}
	
void map_sprite(t_player *p,t_sprite sprite[S_NUMBER])
{
	int	x;
	int	y;
	int	i;

	x = 0;
	i = 0;
	while (p->map[x])
	{
		y =0;
		while(p->map[x][y])
		{
			if (p->map_info[x][y].type == 'S')
			{
		
				printf("%d ------- %d\n",x,y);
				sprite[i].x = y;
				sprite[i].y = x;
				i++;
			}
			y++;
		}
		x++;

	}
}
// t_sprite	*get_sprites(t_prog *prog)
// {
// 	t_queue	*queue;

// 	queue = q_init();
// 	q_enqueue(queue, )
// }
// void sort_sprite(int *order,double *dist,t_sprite *sprite)
// {
// 	int	i;

// 	i = 0;
// 	while (i < S_NUMBER)
// 	{
// 		sprite[i].first = dist[i];
// 		sprite[i].second = order[i];
// 		i++;
// 	}
// }

double	s_dist(double x1, double y1, double x2, double y2)
{
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	sort_sprites(t_sprite *sprite, int len, double x, double y)
{
	double dist;

	dist = s_dist(x,y,sprite->x,sprite->y);
	quicksort()
}

void sprite(t_prog *prog, double *ZBuffer)
{
	t_player	*p;
	int			i;
	int			sprite_order[S_NUMBER];
	t_sprite	sprite[S_NUMBER];
	double		sprite_distance[S_NUMBER];
	double		spriteX;
	double		spriteY;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			spriteHeight;
	int			drawStartY;
	int			drawEndY;
	int			spriteWidth;
	int			drawStartX;
	int			drawEndX;
	int			stripe;
	int			texX;
	int			texY;
	int			texwidth;
	int			y;
	int			d;
	int			color;
	p = &prog->player;
	i = -1;
	while (++i < S_NUMBER)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((p->x - sprite[i].x) * (p->x - sprite[i].x) + (p->y - sprite[i].y) * (p->y - sprite[i].y));
	}
	//sort_sprite(sprite_order,sprite_distance,sprite);

	t_sprite s;
	map_sprite(p,sprite);
	//printf("%f----%f\n",sprite[i].x,sprite[i].y);

	s.x = 3.5;
	s.y = 4.5;
	s.tex = prog->texs[8];

	i = -1;
	while (++i < S_NUMBER)
	{
		spriteX = sprite[i].x - p->x;
		spriteY = sprite[i].y - p->y;
		invDet = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
		transformX = invDet * (p->dir_y * spriteX - p->dir_x * spriteY);
		transformY = invDet * (-p->plane_y * spriteX + p->plane_x * spriteY);
		spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
		spriteHeight = abs((int)(HEIGHT / transformY));
		drawStartY = -spriteHeight / 2   + HEIGHT / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2  + HEIGHT / 2;
		if(drawEndY >= HEIGHT)
			drawEndY = HEIGHT -1;
		spriteWidth = abs((int)(HEIGHT / (transformY)));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
		 	drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX;
		texwidth = get_prog()->texs[0]->width;
		while (stripe < drawEndX)
		{
			texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * get_prog()->texs[0]->width / spriteWidth) / 256;
			if((transformY > 0 && stripe > 0 && stripe < WIDTH) && transformY < ZBuffer[stripe])
			{
				y = drawStartY;
				while (y < drawEndY)
				{
					d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128;
					texY = ((d * get_prog()->texs[0]->height) / spriteHeight) / 256;
					color = get_tex_color(prog->texs[8], texX, texY);
					if((color & 0x00FFFFFF) != 0)
						ft_put_pixel(stripe,y + HEIGHT / 2 - prog->m_y,color);
					y++;
				}
			}
			stripe++;	
		}
	}
}
