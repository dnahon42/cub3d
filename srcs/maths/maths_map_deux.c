/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_map_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:17:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/29 16:44:01 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		init_dda(map, angle_ray);
		draw_line(map, map->cx, map->cy, (int)ray->impact_x, (int)ray->impact_y,
			0x00000);
		i++;
	}
}

static void	get_dda_three(t_map *map, t_ray *ray)
{
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

static void	get_dda_two(t_map *map, t_ray *ray)
{
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
	get_dda_three(map, map->ray);
}

// ici je cherche le sens de mon rayon je calcule ensuite la distance
// jusqu'au premier mur vertical et horizontale
static void	get_dda_one(t_map *map)
{
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
	get_dda_two(map, map->ray);
}

// ici j'init mes valeurs pour cela je transforme mon angle_ray en vecteur en x
// et y il est determiner par l'angle initial de mon joueur
// je les stock car je vais en avoir besoin pour savoir
// dans quel sens je touche le mur
// je convertis aussi la postion de joueur en pixel donc
// si tu effectues le calcul tu tombera sur la position initial du joueur
// je calcule la difference  entre verticale a la suivante
void	init_dda(t_map *map, double angle_ray)
{
	map->dda->hit = 0;
	map->dda->ray_dir_x = cos(angle_ray);
	map->dda->ray_dir_y = sin(angle_ray);
	map->ray->dir_x = map->dda->ray_dir_x;
	map->ray->dir_y = map->dda->ray_dir_y;
	map->ray->angle_ray = angle_ray;
	map->dda->map_x = (int)(map->cx / TILE_SIZE);
	map->dda->map_y = (int)(map->cy / TILE_SIZE);
	map->dda->delta_dist_x = fabs(1 / map->dda->ray_dir_x);
	map->dda->delta_dist_y = fabs(1 / map->dda->ray_dir_y);
	get_dda_one(map);
}
