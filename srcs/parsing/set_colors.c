/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:56:25 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/27 21:42:42 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

static unsigned long	rgb_to_hex(int *rgb)
{
	return (((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + (rgb[2] & 0xff));
}

static int	set_floor_color(t_data *data, char *line)
{
	int (start), (i), (j), (color_idx) = 0;
	data->floor_color = ft_malloc(sizeof(int) * 3);
	if (!data->floor_color)
		return (1);
	i = first_char_index(line, 1);
	while (color_idx < 3)
	{
		start = i;
		while (line[i] && (ft_isdigit(line[i]) || line[i] == '+'
				|| line[i] == '-'))
			i++;
		data->floor_color[color_idx++] = ft_atoi(line + start);
		if (color_idx == 2)
		{
			j = i;
			while (line[j] && (line[j] != '+' && line[j] != '-'
					&& ft_isdigit(line[j]) == 0))
				j++;
			if (ft_isdigit(line[j]) == 0)
				return (data->floor_color[2] = 1000, 1);
		}
		while (line[i] && (line[i] == ',' || ft_isspace(line[i])))
			i++;
	}
	return (data->floor_hex = rgb_to_hex(data->floor_color), 0);
}

static int	set_ceiling_color(t_data *data, char *line)
{
	int (start), (i), (j), (color_idx) = 0;
	data->ceiling_color = ft_malloc(sizeof(int) * 3);
	if (!data->ceiling_color)
		return (1);
	i = first_char_index(line, 1);
	while (color_idx < 3)
	{
		start = i;
		while (line[i] && (ft_isdigit(line[i]) || line[i] == '+'
				|| line[i] == '-'))
			i++;
		data->ceiling_color[color_idx++] = ft_atoi(line + start);
		if (color_idx == 2)
		{
			j = i;
			while (line[j] && (line[j] != '+' && line[j] != '-'
					&& ft_isdigit(line[j]) == 0))
				j++;
			if (ft_isdigit(line[j]) == 0)
				return (data->ceiling_color[2] = 1000, 1);
		}
		while (line[i] && (line[i] == ',' || ft_isspace(line[i])))
			i++;
	}
	return (data->ceiling_hex = rgb_to_hex(data->ceiling_color), 0);
}

static int	is_polluted(char *line)
{
	int (commas), (has_letters), (i) = first_char_index(line, 1);
	commas = 0;
	has_letters = 0;
	while (line[i])
	{
		if (line[i] == ',')
			commas++;
		if (ft_isalpha(line[i]))
			has_letters = 1;
		i++;
	}
	if (commas >= 3 || has_letters)
		return (1);
	return (0);
}

int	set_colors(t_data *data, char *line)
{
	if (!(ft_strlen(line) > 1 && line[1] && ft_isprint(line[1])))
		return (1);
	if (line[0] == 'F' && !(data->floor_color))
	{
		if (is_polluted(line))
			return (1);
		if (set_floor_color(data, line))
			return (1);
	}
	else if (line[0] == 'C' && !(data->ceiling_color))
	{
		if (is_polluted(line))
			return (1);
		if (set_ceiling_color(data, line))
			return (1);
	}
	else
		return (1);
	return (0);
}
