/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphisme_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:21:18 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/28 06:40:44 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_texture(t_map *map, t_data *data)
{
	
	error_texture_NO(map, data);
	error_texture_SO(map, data);
	error_texture_WE(map, data);
	error_texture_EA(map, data);
	return (0);
}

void	draw_background(t_map *map)
{
	char	*dst;

	int(x), (y) = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			dst = map->buffer[map->current].addr + (y
					* map->buffer[map->current].line_length + x
					* (map->buffer[map->current].bpp / 8));
			if (y < HEIGHT / 2)
				*(unsigned int *)dst = map->data->ceiling_hex;
			else
				*(unsigned int *)dst = map->data->floor_hex;
			x++;
		}
		y++;
	}
}

static int	*convert_char_map_to_int(char **char_map, int width, int height)
{
	int	*int_map;

	int(j), (i) = -1;
	int_map = malloc(sizeof(int) * width * height);
	if (!int_map)
		return (NULL);
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (char_map[i][j] == '1')
				int_map[i * width + j] = 1;
			else if (char_map[i][j] == '0')
				int_map[i * width + j] = 0;
		}
	}
	return (int_map);
}

void	init_map(t_map *map, t_data *data)
{
	map->mapx = data->map_highest_x;
	map->mapy = data->map_height;
	map->play = convert_char_map_to_int(data->map, map->mapx, map->mapy);
	if (!map->play)
		exit(1);
}

// Flip marche lets go
t_tex	*choose_texture(t_map *map, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
		{
			ray->flip_x = 0;
			return (&map->mur_EA);
		}
		else
		{
			ray->flip_x = 0;
			return (&map->mur_WE);
		}
	}
	else
	{
		if (ray->dir_y > 0)
		{
			ray->flip_x = 1;
			return (&map->mur_SO);
		}
		else
			return ((ray->flip_x = 0, &map->mur_NO));
	}
}
