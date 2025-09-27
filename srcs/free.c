/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:35:44 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/27 21:17:05 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	destroy_images(t_map *map)
{
	if (map->mur_NO.img)
		mlx_destroy_image(map->mlx, map->mur_NO.img);
	if (map->mur_SO.img)
		mlx_destroy_image(map->mlx, map->mur_SO.img);
	if (map->mur_WE.img)
		mlx_destroy_image(map->mlx, map->mur_WE.img);
	if (map->mur_EA.img)
		mlx_destroy_image(map->mlx, map->mur_EA.img);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	exit_safe(t_map *map)
{
	destroy_images(map);
	if (map->buffer[0].img)
		mlx_destroy_image(map->mlx, map->buffer[0].img);
	if (map->buffer[1].img)
		mlx_destroy_image(map->mlx, map->buffer[1].img);
	if (map->win)
		mlx_destroy_window(map->mlx, map->win);
	if (map->mlx)
		mlx_destroy_display(map->mlx);
	free(map->mlx);
	if (map->play)
		free(map->play);
	exit(1);
}

void	free_parsing(t_data *data)
{
	free(data->ceiling_color);
	free(data->floor_color);
	free_map(data->map);
	free(data->north_wall);
	free(data->east_wall);
	free(data->south_wall);
	free(data->west_wall);
}
