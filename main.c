/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:09:29 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/18 02:19:02 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"
#include "minilibx-linux/mlx.h"

void	init_texture(t_map *map)
{
	map->pos_x = 0;
	map->pos_y = 0;
	map->cx = (int)WIDTH / 2;
	map->cy = (int)HEIGHT / 2;
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

	// case to pixel
	  dy = 0;
	  while (dy < TILE_SIZE)
	  {
		  dx = 0;
		  while (dx < TILE_SIZE)
		  {
			  if (dx == 0 || dy == 0)
				  my_pixel_put(&map->buffer, x * TILE_SIZE + dx, y * TILE_SIZE + dy,
					  0x000000);
		  	else
				  my_pixel_put(&map->buffer, x * TILE_SIZE + dx, y * TILE_SIZE + dy, color);
			  dx++;
		  }
		  dy++;
      map->square_printed = 1;
	  }
  
}

void	draw_map(t_map *map)
{
	int	y;
	int	x;
	
int tmp[441] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,0,0,1,
    1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,
    1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,0,1,1,
    1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,
    1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,1,0,
    1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,
    1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,
    1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,
    1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,
    1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
    1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,
    1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,
    1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
    1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,
    1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

	map->mapx = 21;
	map->mapy = 21;
	map->play = malloc(sizeof(int) * map->mapx * map->mapy);
	if (!map->play)
		exit(1);
	memcpy(map->play, tmp, sizeof(tmp));
	x = 0;
	while (x < map->mapx)
	{
		y = 0;
		while (y < map->mapy)
		{
			if (map->play[y * map->mapx + x] == 1)
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
	map->rot_speed = 0.2;
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
		map->angle -= map->rot_speed;
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
		y  = 0;
		while (y < HEIGHT)
		{
			my_pixel_put(&map->buffer, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_line(t_map *map, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1);
	if (sx == 0)
		sx = -1;
	sy = (y0 < y1);
	if (sy == 0)
		sy = -1;
	err = dx + dy;
	while (1)
	{
		my_pixel_put(&map->buffer, x0, y0, color);
    if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_ray(t_map *map, t_ray *ray)
{
	int x, y;

	// start joueur
	ray->rx = map->cx;
	ray->ry = map->cy;

	// reset angle
	if (ray->ra < 0) 
		ray->ra += 2 * M_PI;
	if (ray->ra >= 2 * M_PI) 
		ray->ra -= 2 * M_PI;

	// direction
	double step = 1; // preci du rayon (px)
	double dx = cos(ray->ra) * step;
  printf("%lf\n",dx);
	double dy = sin(ray->ra) * step;
  printf("%lf\n",dy);

	// avancer jusqu’a un murrrrr
	while (1)
	{
		ray->rx += dx;
		ray->ry += dy;

    //pixel to case
		x = (int)(ray->rx / TILE_SIZE);
		y = (int)(ray->ry / TILE_SIZE);

		// si hors map -> stop
		if (x < 0 || x >= map->mapx || y < 0 || y >= map->mapy)
			break;

		// si mur trouver -> stop
		if (map->play[y * map->mapx + x] == 1)
    {
      printf("GG MUR TROUVER BG\n");
			break;
    }
    
	}
    draw_line(map, map->cx, map->cy, (int)ray->rx, (int)ray->ry, 0xDAFF08);
}

void ft_draw_all_ray(t_map *map,t_ray *ray)
{
  int i = 0;
  double fov;
  fov = 60 * (M_PI /180);
  double angle_step;
  angle_step = fov / (double)WIDTH;

  while(i < WIDTH)
  {
    ray->ra = map->angle - fov / 2 + i * angle_step;
    draw_ray(map,ray);
    i++;
  }
}

int	render_frame(t_map *map)
{
	// clear_image(map, 0x000000);
  draw_map(map);
	draw_player(map);
	ft_draw_all_ray(map, map->ray);
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
	else if (keycode == KEY_ROT_RIGHT)
		map->flag_right = 0;
	else if (keycode == KEY_ROT_LEFT)
		map->flag_left = 0;
	else if (keycode == KEY_EXIT)
		map->flag_exit = 0;
	return (refresh(map));
}

int main(void)
{
    t_map map = (t_map){0};    
    t_ray ray = {0};               
    map.ray = &ray;               

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

