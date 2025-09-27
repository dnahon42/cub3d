/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 02:19:02 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/27 21:58:05 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	info_debug(t_data *data)
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
	t_map	map;
	t_ray	ray;
	t_dda	dda;
	char	**tmp_map;
	char	**old_map;

	t_data(data) = {0};
	if (validate_args(ac, av))
		return (1);
	tmp_map = read_map(av[1]);
	if (!tmp_map)
		return (1);
	old_map = tmp_map;
	data.map = clean_map(tmp_map);
	free_map(old_map);
	if (parsing(&data))
	{
		free_parsing(&data);
		return (1);
	}
	old_map = data.map;
	data.map = make_map_rectangular(&data);
	free_map(old_map);
	if (DEBUG)
		info_debug(&data);
	free((map = (t_map){0}, dda = (t_dda){0}, ray = (t_ray){0}, NULL));
	free((map.dda = &dda, map.ray = &ray, NULL));
	parse_player(&map, &data);
	map.mlx = mlx_init();
	if (!map.mlx)
		return (1);
	map.buffer[0].img = mlx_new_image(map.mlx, WIDTH, HEIGHT);
	map.buffer[0].addr = mlx_get_data_addr(map.buffer[0].img,
			&map.buffer[0].bpp, &map.buffer[0].line_length,
			&map.buffer[0].endian);
	map.buffer[1].img = mlx_new_image(map.mlx, WIDTH, HEIGHT);
	map.buffer[1].addr = mlx_get_data_addr(map.buffer[1].img,
			&map.buffer[1].bpp, &map.buffer[1].line_length,
			&map.buffer[1].endian);
	map.current = 0;
	map.win = mlx_new_window(map.mlx, WIDTH, HEIGHT, "Cub3d");
	if (init_texture(&map, &data))
		return (free_parsing(&data), exit_safe(&map), 1);
	init_map(&map, &data);
	map.data = &data;
	free_parsing(&data);
	mlx_hook(map.win, 2, 1, key_press, &map);
	mlx_hook(map.win, 3, 1, key_release, &map);
	mlx_loop_hook(map.mlx, render_frame, &map);
	mlx_loop(map.mlx);
}
