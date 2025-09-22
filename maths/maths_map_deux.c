/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_map_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:17:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/22 22:46:19 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	get_angle(t_map *map, t_ray *ray)
{
	double	dx;
	double	dy;

	int x, y;
	// start joueur
	ray->rx = map->cx;
	ray->ry = map->cy;
	// reset angle
	if (ray->ra < 0)
		ray->ra += 2 * M_PI;
	if (ray->ra >= 2 * M_PI)
		ray->ra -= 2 * M_PI;
	// direction
	double step = 1; // preci du rayon (px)
	dx = cos(map->ray->angle_ray) * step;
	dy = sin(map->ray->angle_ray) * step;
	// avancer jusqu’a un murrrrr
	while (1)
	{
		ray->rx += dx;
		ray->ry += dy;
		// pixel to case
		x = (int)(ray->rx / TILE_SIZE);
		y = (int)(ray->ry / TILE_SIZE);
		// si hors map -> stop
		if (x < 0 || x >= map->mapx || y < 0 || y >= map->mapy)
			break ;
		// si mur trouver -> stop
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

	i = 0;
	ray->fov = 60 * (M_PI / 180);
	angle_step = ray->fov / (double)WIDTH;
	get_angle(map, map->ray);
	while (i < WIDTH)
	{
		ray->ra = ray->angle_ray - ray->fov / 2 + i * angle_step;
		draw_line(map, map->cx, map->cy, (int)ray->rx, (int)ray->ry, 0xDAFF08);
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
