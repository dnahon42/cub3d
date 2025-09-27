/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_map_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:17:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/27 05:26:57 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

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
		get_dda(map, ray, angle_ray);
		draw_line(map, map->cx, map->cy, (int)ray->impact_x, (int)ray->impact_y,
			0xDAFF08);
		i++;
	}
}
void	draw_colonne(t_map *map, t_ray *ray, int x)
{
	int		y;
	double	dist;
	double	dist_corrected;

	// distance brute entre joueur et point d'impact
	dist = sqrt((ray->impact_x - map->cx) * (ray->impact_x - map->cx)
			+ (ray->impact_y - map->cy) * (ray->impact_y - map->cy));
	// correction du fish-eye
	dist_corrected = dist * cos(ray->angle_ray - map->angle);
	// hauteur de la colonne proportionnelle à la distance corrigée
	ray->lineHauteur = (TILE_SIZE * HEIGHT) / dist_corrected;
	// position de début et fin sur l’ecran
	ray->drawStart = HEIGHT / 2 - ray->lineHauteur / 2;
	ray->drawEnd = HEIGHT / 2 + ray->lineHauteur / 2;
	// C ne pas dépasser l’écran
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
	// Dessin de la colonne en rouge
	y = ray->drawStart;
	while (y <= ray->drawEnd)
	{
		my_pixel_put(&map->buffer[map->current], x, y, 0x00FF0000);
		y++;
	}
}
void	get_dda(t_map *map, t_ray *ray, double angle_ray)
{
	map->dda->hit = 0;
	map->dda->ray_dir_x = cos(angle_ray);
	map->dda->ray_dir_y = sin(angle_ray);
	map->ray->dir_x = map->dda->ray_dir_x;
	map->ray->dir_y = map->dda->ray_dir_y;
	ray->angle_ray = angle_ray;
	map->dda->map_x = (int)(map->cx / TILE_SIZE);
	map->dda->map_y = (int)(map->cy / TILE_SIZE);
	map->dda->delta_dist_x = fabs(1 / map->dda->ray_dir_x);
	map->dda->delta_dist_y = fabs(1 / map->dda->ray_dir_y);
	if (map->dda->ray_dir_x < 0)
	{
		map->dda->step_x = -1;
		map->dda->side_dist_x = (map->cx / TILE_SIZE - map->dda->map_x)
			* map->dda->delta_dist_x;
	}
	else
	{
		map->dda->step_x = 1;
		map->dda->side_dist_x = (map->dda->map_x + 1.0 - map->cx / TILE_SIZE)
			* map->dda->delta_dist_x;
	}
	if (map->dda->ray_dir_y < 0)
	{
		map->dda->step_y = -1;
		map->dda->side_dist_y = (map->cy / TILE_SIZE - map->dda->map_y)
			* map->dda->delta_dist_y;
	}
	else
	{
		map->dda->step_y = 1;
		map->dda->side_dist_y = (map->dda->map_y + 1.0 - map->cy / TILE_SIZE)
			* map->dda->delta_dist_y;
	}
	while (map->dda->hit == 0)
	{
		if (map->dda->side_dist_x < map->dda->side_dist_y)
		{
			map->dda->side_dist_x += map->dda->delta_dist_x;
			map->dda->map_x += map->dda->step_x;
			ray->side = 0;
		}
		else
		{
			map->dda->side_dist_y += map->dda->delta_dist_y;
			map->dda->map_y += map->dda->step_y;
			ray->side = 1;
		}
		if (map->dda->map_x < 0 || map->dda->map_x >= map->mapx
			|| map->dda->map_y < 0 || map->dda->map_y >= map->mapy)
			break ;
		if (map->play[map->dda->map_y * map->mapx + map->dda->map_x] == 1)
			map->dda->hit = 1;
	}
	if (ray->side == 0)
	{
		ray->impact_x = map->cx + (map->dda->side_dist_x
				- map->dda->delta_dist_x) * map->dda->ray_dir_x * TILE_SIZE;
		ray->impact_y = map->cy + (map->dda->side_dist_x
				- map->dda->delta_dist_x) * map->dda->ray_dir_y * TILE_SIZE;
	}
	else
	{
		ray->impact_x = map->cx + (map->dda->side_dist_y
				- map->dda->delta_dist_y) * map->dda->ray_dir_x * TILE_SIZE;
		ray->impact_y = map->cy + (map->dda->side_dist_y
				- map->dda->delta_dist_y) * map->dda->ray_dir_y * TILE_SIZE;
	}
	ray->texture = choose_texture(map, ray);
}
void	draw_texture_one(t_map *map, int x)
{
	double	wall_x;
	double	dist;
	double	dist_corrected;

	dist = sqrt((map->ray->impact_x - map->cx) * (map->ray->impact_x - map->cx)
			+ (map->ray->impact_y - map->cy) * (map->ray->impact_y - map->cy));
	dist_corrected = dist * cos(map->ray->angle_ray - map->angle);
	map->ray->lineHauteur = (TILE_SIZE * HEIGHT) / dist_corrected;
	map->ray->drawStart = HEIGHT / 2 - map->ray->lineHauteur / 2;
	map->ray->drawEnd = HEIGHT / 2 + map->ray->lineHauteur / 2;
	if (map->ray->drawStart < 0)
		map->ray->drawStart = 0;
	if (map->ray->drawEnd >= HEIGHT)
		map->ray->drawEnd = HEIGHT - 1;
	if (!map->ray->texture || !map->ray->texture->addr
		|| map->ray->texture->width <= 0 || map->ray->texture->height <= 0)
		return ;
	if (map->ray->side == 0)
		wall_x = map->ray->impact_y / TILE_SIZE;
	else
		wall_x = map->ray->impact_x / TILE_SIZE;
	check_value(map, wall_x, x);
}

void	check_value(t_map *map, double wall_x, int x)
{
	int	tex_x;

	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * map->ray->texture->width);
	if (map->ray->flip_x)
		tex_x = map->ray->texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= map->ray->texture->width)
		tex_x = map->ray->texture->width - 1;
	draw_texture_two(map, x, tex_x);
}

void	draw_texture_two(t_map *map, int col, int tex_x)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	step = (double)map->ray->texture->height / (double)map->ray->lineHauteur;
	tex_pos = (map->ray->drawStart - HEIGHT / 2 + map->ray->lineHauteur / 2)
		* step;
	y = map->ray->drawStart;
	while (y <= map->ray->drawEnd)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= map->ray->texture->height)
			tex_y = map->ray->texture->height - 1;
		color = get_pixel_from_texture_safe(map->ray->texture, tex_x, tex_y);
		my_pixel_put(&map->buffer[map->current], col, y, color);
		y++;
	}
}
