/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 02:19:02 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/27 08:21:44 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	render_frame(t_map *map)
{
	int		x;
	double	angle_step;
	t_tex	*buf;

	buf = &map->buffer[map->current];
	draw_background(map);
	map->ray->fov = FOV * (M_PI / 180);
	angle_step = map->ray->fov / (double)WIDTH;
	x = 0;
	while (x < WIDTH)
	{
		map->ray->angle_ray = map->angle - (map->ray->fov / 2) + x * angle_step;
		init_dda(map, map->ray->angle_ray);
		draw_texture_one(map, x);
		x++;
	}
	draw_map(map);
	draw_player(map);
	ft_draw_all_ray(map, map->ray);
	mlx_put_image_to_window(map->mlx, map->win, map->buffer[map->current].img,
		0, 0);
	map->current = (map->current + 1) % 2;
	return (0);
}

int	main(void)
{
	t_map	map;
	t_ray	ray;
	t_dda	dda;

	free((map = (t_map){0}, dda = (t_dda){0}, ray = (t_ray){0}, NULL));
	free((map.dda = &dda, map.ray = &ray, NULL));
	map.mlx = mlx_init();
	if (!map.mlx)
		return (1);
	map.buffer[0].img = mlx_new_image(map.mlx, WIDTH, HEIGHT);
	map.buffer[0].addr = mlx_get_data_addr(map.buffer[0].img,
			&map.buffer[0].bpp, &map.buffer[0].line_length,
			&map.buffer[0].endian);
	map.buffer[1].img = mlx_new_image(map.mlx, WIDTH, HEIGHT);
	map.buffer[1].addr = mlx_get_data_addr(map.buffer[1].img,
			&map.buffer[1].bpp, &map.buffer[1].line_length,
			&map.buffer[1].endian);
	map.current = 0;
	map.win = mlx_new_window(map.mlx, WIDTH, HEIGHT, "Cub3d");
	init_texture(&map);
	init_map(&map);
	mlx_hook(map.win, 2, 1, key_press, &map);
	mlx_hook(map.win, 3, 1, key_release, &map);
	mlx_loop_hook(map.mlx, render_frame, &map);
	mlx_loop(map.mlx);
}
