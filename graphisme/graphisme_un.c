/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphisme_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:21:18 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/27 07:50:36 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

// A rajouter pendant parsing
// // Si ton joueur regarde vers le Nord → map->angle = 3 * M_PI / 2;
// Si vers le Sud → map->angle = M_PI / 2;
// Si vers l’Est → map->angle = 0;
// Si vers l’Ouest → map->angle = M_PI
// Position inital a gerer je sais pas ou le faire apparaitre lol
void	init_texture(t_map *map)
{
	map->cx = 10;
	map->cy = 10;
	// Mur NO
	map->mur_NO.img = mlx_xpm_file_to_image(map->mlx, "texture/north.xpm",
			&map->mur_NO.width, &map->mur_NO.height);
	map->mur_NO.addr = mlx_get_data_addr(map->mur_NO.img, &map->mur_NO.bpp,
			&map->mur_NO.line_length, &map->mur_NO.endian);
	// Mur_SO
	map->mur_SO.img = mlx_xpm_file_to_image(map->mlx, "texture/south.xpm",
			&map->mur_SO.width, &map->mur_SO.height);
	map->mur_SO.addr = mlx_get_data_addr(map->mur_SO.img, &map->mur_SO.bpp,
			&map->mur_SO.line_length, &map->mur_SO.endian);
	// Mur_WE
	map->mur_WE.img = mlx_xpm_file_to_image(map->mlx, "texture/west.xpm",
			&map->mur_WE.width, &map->mur_WE.height);
	map->mur_WE.addr = mlx_get_data_addr(map->mur_WE.img, &map->mur_WE.bpp,
			&map->mur_WE.line_length, &map->mur_WE.endian);
	// Mur_EA
	map->mur_EA.img = mlx_xpm_file_to_image(map->mlx, "texture/east.xpm",
			&map->mur_EA.width, &map->mur_EA.height);
	map->mur_EA.addr = mlx_get_data_addr(map->mur_EA.img, &map->mur_EA.bpp,
			&map->mur_EA.line_length, &map->mur_EA.endian);
}

void	draw_background(t_map *map)
{
	char	*dst;

	int x, y;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			dst = map->buffer[map->current].addr + (y
					* map->buffer[map->current].line_length + x
					* (map->buffer[map->current].bpp / 8));
			if (y < HEIGHT / 2)
				// couleurs sol
				*(unsigned int *)dst = 0x878686;
			else
				// couleur toit (ou linverse)
				*(unsigned int *)dst = 0x878686;
			x++;
		}
		y++;
	}
}

void	init_map(t_map *map)
{
	int	tmp[] = {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1,
			1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1};

	map->mapx = 3;
	map->mapy = 13;
	map->play = malloc(sizeof(int) * map->mapx * map->mapy);
	if (!map->play)
		exit(1);
	memcpy(map->play, tmp, sizeof(tmp));
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
			return((ray->flip_x = 0,&map->mur_NO));
	}
}
