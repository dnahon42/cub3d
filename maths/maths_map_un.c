/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_map_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:12:40 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/22 22:51:33 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	draw_vector(t_map *map)
{
	int	l;
	int	i;
	int	x;
	int	y;

	x = 0;
	y = 0;
	map->dir_x = cos(map->angle);
	map->dir_y = sin(map->angle);
	l = 15;
	i = 0;
	while (i < l)
	{
		x = map->cx + i * map->dir_x;
		y = map->cy + i * map->dir_y;
		my_pixel_put(&map->buffer, x, y, 0x0000FF);
		i++;
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
				my_pixel_put(&map->buffer, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}

void	draw_square(t_map *map, int x, int y, int color)
{
	int	dx;
	int	dy;

	// case to pixel
	dy = 0;
	while (dy < TILE_SIZE)
	{
		dx = 0;
		while (dx < TILE_SIZE)
		{
			if (dx == 0 || dy == 0)
				my_pixel_put(&map->buffer, x * TILE_SIZE + dx, y * TILE_SIZE
					+ dy, 0x000000);
			else
				my_pixel_put(&map->buffer, x * TILE_SIZE + dx, y * TILE_SIZE
					+ dy, color);
			dx++;
		}
		dy++;
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

void	draw_line(t_map *map, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1);
	if (sx == 0)
		sx = -1;
	sy = (y0 < y1);
	if (sy == 0)
		sy = -1;
	err = dx + dy;
	while (1)
	{
		my_pixel_put(&map->buffer, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

