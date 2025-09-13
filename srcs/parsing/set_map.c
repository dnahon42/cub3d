/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:01:51 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/13 22:45:06 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

char	**read_map(char *file)
{
	int		fd;
	char	**map;
	char	*line;
	int		rows;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\nFailed to open map\n", 26), NULL);
	map = ft_malloc(sizeof(char *) * 100000);
	if (!map)
		return (write(2, "Error\nMemory allocation failed\n", 31), close(fd),
			NULL);
	rows = 0;
	line = get_next_line(fd);
	if (!line)
		return (ft_free(map), close(fd), write(2, "Error\nFailed to read map\n",
				33), NULL);
	while (line)
	{
		t((map[rows++] = ft_strtrim(line, "\n"), free(line), 0));
		line = get_next_line(fd);
	}
	return (map[rows] = NULL, close(fd), map);
}

char	**clean_map(char **map)
{
	char	**new_map;

	int (i), (y), (index), (len);
	t((i = 0, y = 0, 0));
	while (map[y])
		y++;
	new_map = ft_malloc(sizeof(char *) * (y + 1));
	if (!new_map)
		return (NULL);
	while (map[i])
	{
		index = first_char_index(map[i], 0);
		len = ft_strlen(map[i] + index);
		new_map[i] = ft_malloc(len + 1);
		if (!new_map[i])
		{
			while (--i >= 0)
				ft_free(new_map[i]);
			ft_free(new_map);
			return (NULL);
		}
		ft_strcpy(new_map[i], map[i] + index);
		i++;
	}
	return (new_map[i] = NULL, new_map);
}

int	get_map_start_and_end(t_data *data)
{
	int (found), (i) = 0;
	found = 0;
	while (data->map[i] && !found)
	{
		if (data->map[i][0] == '1' || data->map[i][0] == '0')
		{
			data->map_start = i;
			while (data->map[i] && (data->map[i][0] == '1'
				|| data->map[i][0] == '0'))
				i++;
			data->map_end = i - 1;
			found = 1;
		}
		else
			i++;
	}
	if (found == 0)
		return (ft_putstr_fd(RED BOLD "Error : Missing map\n", 2), 1);
	return (0);
}

void	set_map_highest_x(t_data *data)
{
	int (y) = data->map_start;
	data->map_highest_x = 0;
	while (data->map[y])
	{
		if (data->map_highest_x < find_last_map_element(data->map[y]))
			data->map_highest_x = find_last_map_element(data->map[y]);
		y++;
	}
}
