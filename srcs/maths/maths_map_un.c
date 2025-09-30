/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_map_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:12:40 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/30 15:56:05 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_square(t_map *map, int x, int y, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < TILE_SIZE)
	{
		dx = 0;
		while (dx < TILE_SIZE)
		{
			if (dx == 0 || dy == 0)
				my_pixel_put(&map->buffer[map->current], x * TILE_SIZE + dx, y
					* TILE_SIZE + dy, 0x000000);
			else
				my_pixel_put(&map->buffer[map->current], x * TILE_SIZE + dx, y
					* TILE_SIZE + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_player(t_map *map)
{
	int	x;
	int	y;
	int	r;
	int	dx;
	int	dy;

	y = 0;
	r = 5;
	dx = 0;
	dy = 0;
	x = (map->cx) - r;
	while (x <= (map->cx + r))
	{
		y = (map->cy) - r;
		while (y <= (map->cy + r))
		{
			dx = x - map->cx;
			dy = y - map->cy;
			if (dx * dx + dy * dy <= r * r)
				my_pixel_put(&map->buffer[map->current], x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}

void	draw_map(t_map *map)
{
	map->x = 0;
	while (map->x < map->mapx)
	{
		map->y = 0;
		while (map->y < map->mapy)
		{
			if (map->play[map->y * map->mapx + map->x] == 1)
				draw_square(map, map->x, map->y, 0x828282);
			else
				draw_square(map, map->x, map->y, 0xFFFFFF);
			map->y++;
		}
		map->x++;
	}
}
// void	draw_line(t_map *map, int x0, int y0, int x1, int y1, int color)
// {
// 	while (1)
// 	{
// 		my_pixel_put(&map->buffer[map->current], x0, y0, color);
// 		if (x0 == x1 && y0 == y1)
// 			break ;
// 		map->e2 = 2 * map->err;
// 		if (map->e2 >= map->dy)
// 		{
// 			map->err += map->dy;
// 			x0 += map->sx;
// 		}
// 		if (map->e2 <= map->dx)
// 		{
// 			map->err += map->dx;
// 			y0 += map->sy;
// 		}
// 	}
// }
// void	init_line(t_map *map, int x0, int y0, int x1, int y1, int color)
// {
// 	(void)color;
// 	map->dx = abs(x1 - x0);
// 	map->dy = -abs(y1 - y0);
// 	map->sx = (x0 < x1);
// 	if (map->sx == 0)
// 		map->sx = -1;
// 	map->sy = (y0 < y1);
// 	if (map->sy == 0)
// 		map->sy = -1;
// 	map->err = map->dx + map->dy;
// 	draw_line(map,x0,y0,x1,y1,color);
// }
