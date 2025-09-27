/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphisme_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 04:16:03 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/27 05:23:55 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	get_pixel_from_texture_safe(t_tex *tex, int x, int y)
{
	char	*dst;
	int		color;

	if (!tex || !tex->addr)
		return (0xFF00FF); // debug rose
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0x00FF00); // debug vert
	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	color = *(unsigned int *)dst; 
	return (color);
}
void	my_pixel_put(t_tex *img, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}