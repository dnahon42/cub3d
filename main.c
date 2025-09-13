/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:43:18 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/13 18:36:25 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"
#include "minilibx-linux/mlx.h"

void	draw_player(t_map *map)
{
	map->pos_x = 1;
	map->pos_y = 1;
	map->player = mlx_xpm_file_to_image(map->mlx, "player/point.xpm",
			&map->img_height, &map->img_width);
	mlx_put_image_to_window(map->mlx, map->win, map->player, map->pos_x * 10,
		map->pos_y * 10);
}

void	ft_moove(t_map *map)
{
	map->new_pos_x = map->pos_x;
	map->new_pos_y = map->pos_y;
	if (map->flag_w == 1)
		map->new_pos_y--;
	if (map->flag_s == 1)
		map->new_pos_y++;
	if (map->flag_a == 1)
		map->new_pos_x--;
	if (map->flag_d == 1)
		map->new_pos_x++;
}

void	init_flag(t_map *map)
{
	map->flag_w = 0;
	map->flag_s = 0;
	map->flag_a = 0;
	map->flag_d = 0;
}

void	render_player(t_map *map)
{
	mlx_clear_window(map->mlx, map->win);
	mlx_put_image_to_window(map->mlx, map->win, map->player, map->pos_x * 10,
		map->pos_y * 10);
}

int	refresh(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	ft_moove(map);
	init_flag(map);
	map->pos_x = map->new_pos_x;
	map->pos_y = map->new_pos_y;
	render_player(map);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keycode == KEY_UP)
		map->flag_w = 1;
	else if (keycode == KEY_DOWN)
		map->flag_s = 1;
	else if (keycode == KEY_LEFT)
		map->flag_a = 1;
	else if (keycode == KEY_RIGHT)
		map->flag_d = 1;
	else if (keycode == KEY_EXIT)
		exit(1);
	return (refresh(map));
}

int	key_release(int keycode, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keycode == KEY_LEFT)
		map->flag_a = 0;
	else if (keycode == KEY_RIGHT)
		map->flag_d = 0;
	else if (keycode == KEY_UP)
		map->flag_w = 0;
	else if (keycode == KEY_DOWN)
		map->flag_s = 0;
	else if (keycode == KEY_EXIT)
		map->flag_exit = 0;
	return (refresh(map));
}

void	ft_exec(t_map *map)
{
	mlx_hook(map->win, 2, 1, key_press, map);
	mlx_hook(map->win, 3, 1, key_release, map);
	render_player(map);
	mlx_loop(map->mlx);
}

int	main(void)
{
	t_map(map) = {0};
	map.mlx = mlx_init();
	if (!map.mlx)
		return (1);
	map.win = mlx_new_window(map.mlx, 1000, 1000, "Cub3d");
	draw_player(&map);
	ft_exec(&map);
	mlx_loop(map.mlx);
}
