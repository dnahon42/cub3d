/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 02:19:02 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/22 22:48:51 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	render_frame(t_map *map)
{
	int		x;
	double	angle_step;

	x = 0;
	clear_image(map, 0x000000);
	map->ray->fov = 60 * (M_PI / 180);
	angle_step = map->ray->fov / (double)WIDTH;
	while (x < WIDTH)
	{
		map->ray->angle_ray = map->angle - (map->ray->fov / 2) + x
			* (map->ray->fov / WIDTH);
		get_angle(map, map->ray);
		draw_colonne(map, map->ray, x);
		x++;
	}
	draw_map(map);
	draw_player(map);
	ft_draw_all_ray(map, map->ray);
	mlx_put_image_to_window(map->mlx, map->win, map->buffer.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_map	map;
	t_ray	ray;

	map = (t_map){0};
	ray = (t_ray){0};
	map.ray = &ray;
	map.mlx = mlx_init();
	if (!map.mlx)
		return (1);
	map.buffer.img = mlx_new_image(map.mlx, WIDTH, HEIGHT);
	map.buffer.addr = mlx_get_data_addr(map.buffer.img, &map.buffer.bpp,
			&map.buffer.line_length, &map.buffer.endian);
	map.win = mlx_new_window(map.mlx, WIDTH, HEIGHT, "Cub3d");
	init_texture(&map);
	init_map(&map);
	mlx_hook(map.win, 2, 1, key_press, &map);
	mlx_hook(map.win, 3, 1, key_release, &map);
	mlx_loop_hook(map.mlx, render_frame, &map);
	mlx_loop(map.mlx);
}
