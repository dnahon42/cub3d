/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 06:14:40 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/29 16:45:38 by dnahon           ###   ########.fr       */
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
	map->mur_NO.img = mlx_xpm_file_to_image(map->mlx, data->north_wall,
			&map->mur_NO.width, &map->mur_NO.height);
	if (!map->mur_NO.img)
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_NORTH_TEXTURE RESET), map));
	}
	map->mur_NO.addr = mlx_get_data_addr(map->mur_NO.img, &map->mur_NO.bpp,
			&map->mur_NO.line_length, &map->mur_NO.endian);
}

void	error_texture_ea(t_map *map, t_data *data)
{
	if (verify_texture_paths(data))
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_EAST_TEXTURE RESET), map));
	}
	map->mur_EA.img = mlx_xpm_file_to_image(map->mlx, data->east_wall,
			&map->mur_EA.width, &map->mur_EA.height);
	if (!map->mur_EA.img)
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_EAST_TEXTURE RESET), map));
	}
	map->mur_EA.addr = mlx_get_data_addr(map->mur_NO.img, &map->mur_EA.bpp,
			&map->mur_EA.line_length, &map->mur_EA.endian);
}

void	error_texture_we(t_map *map, t_data *data)
{
	if (verify_texture_paths(data))
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_WEST_TEXTURE RESET), map));
	}
	map->mur_WE.img = mlx_xpm_file_to_image(map->mlx, data->west_wall,
			&map->mur_WE.width, &map->mur_WE.height);
	if (!map->mur_WE.img)
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_WEST_TEXTURE RESET), map));
	}
	map->mur_WE.addr = mlx_get_data_addr(map->mur_WE.img, &map->mur_WE.bpp,
			&map->mur_WE.line_length, &map->mur_WE.endian);
}

void	error_texture_so(t_map *map, t_data *data)
{
	if (verify_texture_paths(data))
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_SOUTH_TEXTURE RESET), map));
	}
	map->mur_SO.img = mlx_xpm_file_to_image(map->mlx, data->south_wall,
			&map->mur_SO.width, &map->mur_SO.height);
	if (!map->mur_SO.img)
	{
		free_parsing(data);
		exit_safe((printf(BOLD RED ERR_SOUTH_TEXTURE RESET), map));
	}
	map->mur_SO.addr = mlx_get_data_addr(map->mur_SO.img, &map->mur_SO.bpp,
			&map->mur_SO.line_length, &map->mur_SO.endian);
}
