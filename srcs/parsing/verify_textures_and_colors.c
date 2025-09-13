/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_textures_and_colors.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:58:29 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/13 22:45:12 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

int	verify_texture_paths(t_data *data)
{
	if (!(data->north_wall) || !(data->east_wall) || !(data->south_wall)
		|| !(data->west_wall))
		return (ft_putstr_fd(RED BOLD ERR_TEXTURE_MISSING RESET, 2), 1);
	if (!(ft_strncmp(".xpm", data->north_wall + (ft_strlen(data->north_wall)
					- 4), 4) == 0))
		return (ft_putstr_fd(RED BOLD ERR_TEXTURE RESET, 2), 1);
	if (!(ft_strncmp(".xpm", data->east_wall + (ft_strlen(data->east_wall) - 4),
				4) == 0))
		return (ft_putstr_fd(RED BOLD ERR_TEXTURE RESET, 2), 1);
	if (!(ft_strncmp(".xpm", data->south_wall + (ft_strlen(data->south_wall)
					- 4), 4) == 0))
		return (ft_putstr_fd(RED BOLD ERR_TEXTURE RESET, 2), 1);
	if (!(ft_strncmp(".xpm", data->west_wall + (ft_strlen(data->west_wall) - 4),
				4) == 0))
		return (ft_putstr_fd(RED BOLD ERR_TEXTURE RESET, 2), 1);
	return (0);
}

int	verify_colors(t_data *data)
{
	if (!(data->floor_color) || !(data->ceiling_color))
		return (1);
	else if (data->floor_color[0] > 255 || data->floor_color[0] < 0)
		return (1);
	else if (data->floor_color[1] > 255 || data->floor_color[1] < 0)
		return (1);
	else if (data->floor_color[2] > 255 || data->floor_color[2] < 0)
		return (1);
	if (data->ceiling_color[0] > 255 || data->ceiling_color[0] < 0)
		return (1);
	else if (data->ceiling_color[1] > 255 || data->ceiling_color[1] < 0)
		return (1);
	else if (data->ceiling_color[2] > 255 || data->ceiling_color[2] < 0)
		return (1);
	return (0);
}
