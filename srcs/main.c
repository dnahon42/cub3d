/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:43:18 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/13 22:44:32 by dnahon           ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data(data) = {0};
	if (validate_args(ac, av))
		return (1);
	data.map = read_map(av[1]);
	if (!data.map)
		return (1);
	data.map = clean_map(data.map);
	if (parsing(&data))
		return (1);
}
