/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:32:01 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/14 20:23:16 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

int	check_map_elements(t_data *data)
{
	int (x), (x_max), (is_invalid), (found), (y) = data->map_start;
	found = 0;
	is_invalid = 0;
	while (data->map[y])
	{
		x = 0;
		x_max = ft_strlen(data->map[y]);
		while (data->map[y][x] && x < x_max)
		{
			if (data->map[y][x] == 'E' || data->map[y][x] == 'W'
				|| data->map[y][x] == 'S' || data->map[y][x] == 'N')
				found++;
			if (data->map[y][x] != 'E' && data->map[y][x] != 'W'
				&& data->map[y][x] != 'S' && data->map[y][x] != 'N'
				&& data->map[y][x] != '1' && data->map[y][x] != ' '
				&& data->map[y][x] != '0')
				is_invalid = 1;
			x++;
		}
		y++;
	}
	if (found == 0 || found > 1 || is_invalid)
		return (1);
	return (0);
}

int	verify_last_map_element(t_data *data, int i)
{
	int (j) = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != ' ' && data->map[i][j] != '\t'
				&& data->map[i][j] != '\r' && data->map[i][j] != '\n'
				&& data->map[i][j] != '\v' && data->map[i][j] != '\f')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
