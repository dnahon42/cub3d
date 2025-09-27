/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:43:18 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/14 20:23:48 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../libft/includes/get_next_line.h"
#include "../libft/includes/libft.h"

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
	return (0);
}

void	info_debug(t_data *data)
{
	int (i) = -1;
	printf(GREEN BOLD "Map after cleaning : \n" RESET);
	while (data->map[++i])
		printf("\033[41;37m%s\033[0m\n", data->map[i]);
	if (data->north_wall)
		printf(BOLD CYAN "North wall texture : %s\n", data->north_wall);
	if (data->east_wall)
		printf(BOLD CYAN "East wall texture : %s\n", data->east_wall);
	if (data->south_wall)
		printf(BOLD CYAN "South wall texture : %s\n", data->south_wall);
	if (data->west_wall)
		printf(BOLD CYAN "West wall texture : %s\n", data->west_wall);
	if (data->ceiling_color)
		printf(BOLD CYAN "Ceiling RGB : %d, %d, %d\n", data->ceiling_color[0],
			data->ceiling_color[1], data->ceiling_color[2]);
	if (data->floor_color)
		printf(BOLD CYAN "Floor RGB : %d, %d, %d\n", data->floor_color[0],
			data->floor_color[1], data->floor_color[2]);
	printf(BOLD CYAN "Ceiling Hex : %ld\n", data->ceiling_hex);
	printf(BOLD CYAN "Floor Hex : %ld\n", data->floor_hex);
	printf(BOLD CYAN "Map start : %d\n", data->map_start);
	printf(BOLD CYAN "Map end : %d\n", data->map_end);
	printf(BOLD CYAN "Map height : %d\n", data->map_height);
	printf(BOLD CYAN "Map highest x : %d\n" RESET, data->map_highest_x);
}

int	main(int ac, char **av)
{
	t_data (data) = {0};
	if (validate_args(ac, av))
		return (1);
	data.map = read_map(av[1]);
	if (!data.map)
		return (1);
	data.map = clean_map(data.map);
	if (parsing(&data))
		return (1);
	data.map = make_map_rectangular(&data);
	if (DEBUG)
		info_debug(&data);
}
