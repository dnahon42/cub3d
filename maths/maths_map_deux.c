/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_map_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:17:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/23 00:07:32 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	get_angle(t_map *map, t_ray *ray, double angle_ray)
{
	double	dx;
	double	dy;
	int		x;
	int		y;

	dx = cos(angle_ray);
	dy = sin(angle_ray);
	ray->rx = map->cx;
	ray->ry = map->cy;
	while (1)
	{
		ray->rx += dx;
		ray->ry += dy;
		x = ray->rx / TILE_SIZE;
		y = ray->ry / TILE_SIZE;
		if (x < 0 || x >= map->mapx || y < 0 || y >= map->mapy)
			break ;
		if (map->play[y * map->mapx + x] == 1)
			break ;
	}
	ray->impact_x = ray->rx;
	ray->impact_y = ray->ry;
}

void	ft_draw_all_ray(t_map *map, t_ray *ray)
{
	int		i;
	double	angle_step;
	double	angle_ray;

	i = 0;
	ray->fov = 60 * (M_PI / 180);
	angle_step = ray->fov / (double)WIDTH;
	while (i < WIDTH)
	{
		angle_ray = map->angle - ray->fov / 2 + i * angle_step;
		get_angle(map, ray, angle_ray);
		draw_line(map, map->cx, map->cy, (int)ray->impact_x, (int)ray->impact_y,
			0xDAFF08);
		i++;
	}
}

void	draw_colonne(t_map *map, t_ray *ray, int x)
{
	int	y;

	ray->dist = sqrt((ray->impact_x - map->cx) * (ray->impact_x - map->cx)
			+ (ray->impact_y - map->cy) * (ray->impact_y - map->cy));
	ray->fisheye = ray->dist * cos(map->ray->angle_ray - map->angle);
	ray->lineHauteur = (TILE_SIZE * HEIGHT) / ray->dist;
	ray->drawStart = HEIGHT / 2 - ray->lineHauteur / 2;
	ray->drawEnd = HEIGHT / 2 + ray->lineHauteur / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
	y = ray->drawStart;
	while (y <= ray->drawEnd)
	{
		my_pixel_put(&map->buffer, x, y, 0xee1400);
		y++;
	}
}
