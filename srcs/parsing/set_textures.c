/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:59:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/13 22:45:08 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

char	*get_texture_path(char *line)
{
	char	*texture_path;

	int (copy_index), (j), (i) = 2;
	copy_index = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	j = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	texture_path = ft_malloc((i - j) + 1);
	if (!texture_path)
		return (NULL);
	ft_strncpy(texture_path, line + j, i - j);
	texture_path[i - j] = '\0';
	return (texture_path);
}

int	set_wall_textures(t_data *data, char *line)
{
	if (!(ft_strlen(line) > 2 && line[2] && ft_isprint(line[2])))
		return (1);
	if (line[0] == 'N' && line[1] == 'O' && (data->north_wall))
		return (2);
	else if (line[0] == 'S' && line[1] == 'O' && (data->south_wall))
		return (2);
	else if (line[0] == 'W' && line[1] == 'E' && (data->west_wall))
		return (2);
	else if (line[0] == 'E' && line[1] == 'A' && (data->east_wall))
		return (2);
	else if (line[0] == 'N' && line[1] == 'O' && !(data->north_wall))
		data->north_wall = get_texture_path(line);
	else if (line[0] == 'S' && line[1] == 'O' && !(data->south_wall))
		data->south_wall = get_texture_path(line);
	else if (line[0] == 'W' && line[1] == 'E' && !(data->west_wall))
		data->west_wall = get_texture_path(line);
	else if (line[0] == 'E' && line[1] == 'A' && !(data->east_wall))
		data->east_wall = get_texture_path(line);
	else
		return (1);
	return (0);
}
