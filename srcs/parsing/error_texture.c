/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 06:14:40 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/30 15:41:42 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

void	error_texture_no(t_map *map, t_data *data)
{
	if (verify_texture_paths(data))
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_NORTH_TEXTURE RESET), map));
	}
	map->mur_no.img = mlx_xpm_file_to_image(map->mlx, data->north_wall,
			&map->mur_no.width, &map->mur_no.height);
	if (!map->mur_no.img)
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_NORTH_TEXTURE RESET), map));
	}
	map->mur_no.addr = mlx_get_data_addr(map->mur_no.img, &map->mur_no.bpp,
			&map->mur_no.line_length, &map->mur_no.endian);
}

void	error_texture_ea(t_map *map, t_data *data)
{
	if (verify_texture_paths(data))
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_EAST_TEXTURE RESET), map));
	}
	map->mur_ea.img = mlx_xpm_file_to_image(map->mlx, data->east_wall,
			&map->mur_ea.width, &map->mur_ea.height);
	if (!map->mur_ea.img)
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_EAST_TEXTURE RESET), map));
	}
	map->mur_ea.addr = mlx_get_data_addr(map->mur_no.img, &map->mur_ea.bpp,
			&map->mur_ea.line_length, &map->mur_ea.endian);
}

void	error_texture_we(t_map *map, t_data *data)
{
	if (verify_texture_paths(data))
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_WEST_TEXTURE RESET), map));
	}
	map->mur_we.img = mlx_xpm_file_to_image(map->mlx, data->west_wall,
			&map->mur_we.width, &map->mur_we.height);
	if (!map->mur_we.img)
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_WEST_TEXTURE RESET), map));
	}
	map->mur_we.addr = mlx_get_data_addr(map->mur_we.img, &map->mur_we.bpp,
			&map->mur_we.line_length, &map->mur_we.endian);
}

void	error_texture_so(t_map *map, t_data *data)
{
	if (verify_texture_paths(data))
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_SOUTH_TEXTURE RESET), map));
	}
	map->mur_so.img = mlx_xpm_file_to_image(map->mlx, data->south_wall,
			&map->mur_so.width, &map->mur_so.height);
	if (!map->mur_so.img)
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_SOUTH_TEXTURE RESET), map));
	}
	map->mur_so.addr = mlx_get_data_addr(map->mur_so.img, &map->mur_so.bpp,
			&map->mur_so.line_length, &map->mur_so.endian);
}
