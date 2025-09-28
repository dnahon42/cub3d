/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:41:17 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/28 19:56:09 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

static char	*make_map_row(char *src, int width, int is_top_or_bottom)
{
	char	*row;

	int(line_len), (j) = -1;
	line_len = ft_strlen(src);
	row = ft_malloc(sizeof(char) * (width + 1));
	if (!row)
		return (NULL);
	while (++j < width)
	{
		if (j < line_len)
		{
			if (src[j] == ' ')
				row[j] = '1';
			else
				row[j] = src[j];
		}
		else
		{
			if (is_top_or_bottom || j == width - 1)
				row[j] = '1';
			else
				row[j] = '0';
		}
	}
	return (row[j] = '\0', row);
}

static void	free_map_rows(char **map, int last_row)
{
	while (--last_row >= 0)
		ft_free(map[last_row]);
	ft_free(map);
}

char	**make_map_rectangular(t_data *data)
{
	char **new_map;

	int(map_rows), (row), (map_row) = data->map_start;
	map_rows = data->map_end - data->map_start + 1;
	new_map = ft_malloc(sizeof(char *) * (map_rows + 1));
	if (!new_map)
		return (NULL);
	row = 0;
	while (map_row <= data->map_end)
	{
		if (row == 0 || map_row == data->map_end)
			new_map[row] = make_map_row(data->map[map_row], data->map_highest_x,
					1);
		else
			new_map[row] = make_map_row(data->map[map_row], data->map_highest_x,
					0);
		if (!new_map[row])
			return (free_map_rows(new_map, row), NULL);

		row++;
		map_row++;
		}
		new_map[row] = NULL;
		return (new_map);
	}
