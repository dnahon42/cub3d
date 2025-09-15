/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:09:29 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/16 00:12:37 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"
#include "minilibx-linux/mlx.h"

void	init_texture(t_map *map)
{
	map->pos_x = 0;
	map->pos_y = 0;
	map->mur.img = mlx_xpm_file_to_image(map->mlx, "player/mur.xpm",
			&map->mur.width, &map->mur.height);
	map->mur.addr = mlx_get_data_addr(map->mur.img, &map->mur.bpp,
			&map->mur.line_length, &map->mur.endian);
	map->sol.img = mlx_xpm_file_to_image(map->mlx, "player/sol.xpm",
			&map->sol.width, &map->sol.height);
	map->sol.addr = mlx_get_data_addr(map->sol.img, &map->sol.bpp,
			&map->sol.line_length, &map->sol.endian);
}

void	my_pixel_put(t_tex *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_vector(t_map *map)
{
	int	l;
	int	i;
	int	x;
	int	y;

	x = 0;
	y = 0;
	map->dir_x = cos(map->angle);
	map->dir_y = sin(map->angle);
	l = 50;
	i = 0;
	while (i < l)
	{
		x = map->cx + i * map->dir_x;
		y = map->cy + i * map->dir_y;
		my_pixel_put(&map->buffer, x, y, 0x0000FF);
		i++;
	}
}

void	draw_player(t_map *map)
{
	int	x;
	int	y;
	int	r;
	int	dx;
	int	dy;

	y = 0;
	r = 20;
	dx = 0;
	dy = 0;
	x = (map->cx) - r;
	while (x <= (map->cx + r))
	{
		y = (map->cy) - r;
		while (y <= (map->cy + r))
		{
			dx = x - map->cx;
			dy = y - map->cy;
			if (dx * dx + dy * dy <= r * r)
				my_pixel_put(&map->buffer, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
	draw_vector(map);
}

void	draw_square(t_map *map, int x, int y, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < 100)
	{
		dx = 0;
		while (dx < 100)
		{
			if (dx == 0 || dy == 0)
				my_pixel_put(&map->buffer, x * 100 + dx, y * 100 + dy,
					0x000000);
			else
				my_pixel_put(&map->buffer, x * 100 + dx, y * 100 + dy, color);
			dx++;
		}
		dy++;
	}
}
void	draw_map(t_map *map)
{
	int	y;
	int	x;
	int	play[] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 1};

	map->mapx = 4;
	map->mapy = 6;
	x = 0;
	while (x < map->mapx)
	{
		y = 0;
		while (y < map->mapy)
		{
			if (play[y * map->mapx + x] == 1)
				draw_square(map, x, y, 0x828282);
			else
				draw_square(map, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}

void	ft_moove(t_map *map)
{
	map->move_speed = 2;
	map->rot_speed = 2;
	map->new_pos_x = map->cx;
	map->new_pos_y = map->cy;
	if (map->flag_w)
	{
		map->new_pos_x += map->dir_x * map->move_speed;
		map->new_pos_y += map->dir_y * map->move_speed;
	}
	if (map->flag_s)
	{
		map->new_pos_x -= map->dir_x * map->move_speed;
		map->new_pos_y -= map->dir_y * map->move_speed;
	}
	if (map->flag_a)
	{
		map->new_pos_x -= map->dir_y * map->move_speed;
		map->new_pos_y += map->dir_x * map->move_speed;
	}
	if (map->flag_d)
	{
		map->new_pos_x += map->dir_y * map->move_speed;
		map->new_pos_y -= map->dir_x * map->move_speed;
	}
	if (map->flag_left)
		map->angle -= map->move_speed;
	if (map->flag_right)
		map->angle += map->rot_speed;
	map->dir_x = cos(map->angle);
	map->dir_y = sin(map->angle);
	map->cx = map->new_pos_x;
	map->cy = map->new_pos_y;
}

void	init_flag(t_map *map)
{
	map->flag_w = 0;
	map->flag_s = 0;
	map->flag_a = 0;
	map->flag_d = 0;
	map->flag_right = 0;
	map->flag_left = 0;
}

void	clear_image(t_map *map, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			my_pixel_put(&map->buffer, x, y, color);
			y++;
		}
		x++;
	}
}

int	render_frame(t_map *map)
{
	clear_image(map, 0x000000);
	draw_map(map);
	draw_player(map);
	mlx_put_image_to_window(map->mlx, map->win, map->buffer.img, 0, 0);
	return (0);
}

int	refresh(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	ft_moove(map);
	init_flag(map);
	map->cx = map->new_pos_x;
	map->cy = map->new_pos_y;
	render_frame(map);
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
	else if (keycode == KEY_ROT_RIGHT)
		map->flag_right = 1;
	else if (keycode == KEY_ROT_LEFT)
		map->flag_left = 1;
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

int	main(void)
{
	t_map(map) = {0};
	map.mlx = mlx_init();
	if (!map.mlx)
		return (1);
	map.buffer.img = mlx_new_image(map.mlx, WIDTH, HEIGHT);
	map.buffer.addr = mlx_get_data_addr(map.buffer.img, &map.buffer.bpp,
			&map.buffer.line_length, &map.buffer.endian);
	map.win = mlx_new_window(map.mlx, WIDTH, HEIGHT, "Cub3d");
	init_texture(&map);
	mlx_hook(map.win, 2, 1, key_press, &map);
	mlx_hook(map.win, 3, 1, key_release, &map);
	mlx_loop_hook(map.mlx, render_frame, &map);
	mlx_loop(map.mlx);
}
