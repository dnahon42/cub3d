/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_map_trois.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:20:38 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/27 21:37:49 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_texture_two(t_map *map, int col, int tex_x)
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

static void	check_value(t_map *map, double wall_x, int x)
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
