/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphisme_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:21:18 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/27 21:58:27 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_texture(t_map *map, t_data *data)
{
	map->mur_NO.img = mlx_xpm_file_to_image(map->mlx, data->north_wall,
			&map->mur_NO.width, &map->mur_NO.height);
	if (!map->mur_NO.img)
		return(printf(BOLD RED ERR_NORTH_TEXTURE RESET), 1);
	map->mur_NO.addr = mlx_get_data_addr(map->mur_NO.img, &map->mur_NO.bpp,
			&map->mur_NO.line_length, &map->mur_NO.endian);
	map->mur_SO.img = mlx_xpm_file_to_image(map->mlx, data->south_wall,
			&map->mur_SO.width, &map->mur_SO.height);
	if (!map->mur_SO.img)
		return(printf(BOLD RED ERR_SOUTH_TEXTURE RESET), 1);
	map->mur_SO.addr = mlx_get_data_addr(map->mur_SO.img, &map->mur_SO.bpp,
			&map->mur_SO.line_length, &map->mur_SO.endian);
	map->mur_WE.img = mlx_xpm_file_to_image(map->mlx, data->west_wall,
			&map->mur_WE.width, &map->mur_WE.height);
	if (!map->mur_WE.img)
		return(printf(BOLD RED ERR_WEST_TEXTURE RESET), 1);
	map->mur_WE.addr = mlx_get_data_addr(map->mur_WE.img, &map->mur_WE.bpp,
			&map->mur_WE.line_length, &map->mur_WE.endian);
	map->mur_EA.img = mlx_xpm_file_to_image(map->mlx, data->east_wall,
			&map->mur_EA.width, &map->mur_EA.height);
	if (!map->mur_EA.img)
		return(printf(BOLD RED ERR_EAST_TEXTURE RESET), 1);
	map->mur_EA.addr = mlx_get_data_addr(map->mur_EA.img, &map->mur_EA.bpp,
			&map->mur_EA.line_length, &map->mur_EA.endian);
	return (0);
}

void	draw_background(t_map *map)
{
	char	*dst;

	int (x), (y) = 0;
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

	int (j), (i) = -1;
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
