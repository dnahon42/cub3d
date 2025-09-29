/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphisme_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 04:16:03 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/29 16:43:59 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_pixel_from_texture_safe(t_tex *tex, int x, int y)
{
	char	*dst;
	int		color;

	if (!tex || !tex->addr)
		return (0xFF00FF);
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0x00FF00);
	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	my_pixel_put(t_tex *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render_frame(t_map *map)
{
	int		x;
	double	angle_step;
	t_tex	*buf;

	buf = &map->buffer[map->current];
	draw_background(map);
	map->ray->fov = 60 * (M_PI / 180);
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
