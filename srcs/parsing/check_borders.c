/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:21:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/27 21:41:52 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

static int	check_top_wall(t_data *data)
{
	int (x), (y) = data->map_start;
	x = 0;
	if (data->map[y])
	{
		while (data->map[y][x] && x < data->map_highest_x)
		{
			if (data->map[y][x] != '1' && data->map[y][x] != ' ')
				return (1);
			x++;
		}
	}
	else
		return (1);
	return (0);
}

static int	check_bottom_wall(t_data *data)
{
	int (x), (y) = data->map_end;
	x = 0;
	if (data->map[y])
	{
		while (data->map[y][x] && x < data->map_highest_x)
		{
			if (data->map[y][x] != '1' && data->map[y][x] != ' ')
				return (1);
			x++;
		}
	}
	else
		return (1);
	return (0);
}

static int	check_left_wall(t_data *data)
{
	int (y) = data->map_start;
	while (data->map[y] && y < data->map_end)
	{
		if (data->map[y][0] != '1' && data->map[y][0] != ' ')
			return (1);
		y++;
	}
	return (0);
}

static int	check_right_wall(t_data *data)
{
	int (x), (y) = data->map_start;
	while (data->map[y] && y < data->map_end)
	{
		x = ft_strlen(data->map[y]) - 1;
		if (data->map[y][x] != '1' && data->map[y][x] != ' ')
			return (1);
		y++;
	}
	return (0);
}

int	check_borders(t_data *data)
{
	if (check_top_wall(data))
		return (1);
	if (check_bottom_wall(data))
		return (1);
	if (check_left_wall(data))
		return (1);
	if (check_right_wall(data))
		return (1);
	return (0);
}
