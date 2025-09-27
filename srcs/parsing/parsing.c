/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:16:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/27 21:16:53 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

int	parsing(t_data *data)
{
	int (i) = -1;
	if (get_map_start_and_end(data))
		return (1);
	if (verify_last_map_element(data, data->map_end + 1))
		return (ft_putstr_fd(RED BOLD ERR_LAST_ELEMENT RESET, 2), 1);
	set_map_highest_x(data);
	if (check_borders(data))
		return (ft_putstr_fd(RED BOLD ERR_WALL_MISSING RESET, 2), 1);
	if (check_map_elements(data))
		return (ft_putstr_fd(RED BOLD ERR_MAP_ELEMENTS RESET, 2), 1);
	while (data->map[++i])
	{
		if (set_wall_textures(data, data->map[i]) == 2)
			return (ft_putstr_fd(RED BOLD ERR_DUPLICATE_TEXTURE RESET, 2), 1);
		set_colors(data, data->map[i]);
	}
	if (verify_colors(data))
		return (ft_putstr_fd(RED BOLD ERR_COLORS RESET, 2), 1);
	if (verify_texture_paths(data) == 1)
		return (1);
	data->map_height = data->map_end - data->map_start + 1;
	return (0);
}

void	parse_player(t_map *map, t_data *data)
{
	char	c;

	int (x), (y) = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_highest_x)
		{
			c = data->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				map->cx = (x * TILE_SIZE) + 0.5f;
				map->cy = (y * TILE_SIZE) + 0.5f;
				if (c == 'N')
					map->angle = 3 * M_PI / 2;
				else if (c == 'S')
					map->angle = M_PI / 2;
				else if (c == 'E')
					map->angle = 0;
				else if (c == 'W')
					map->angle = M_PI;
				data->map[y][x] = '0';
			}
		}
	}
}
