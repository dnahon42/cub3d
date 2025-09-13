/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:00:13 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/13 22:45:10 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/includes/get_next_line.h"
#include "../../libft/includes/libft.h"

void	t(int a)
{
	(void)a;
}

int	validate_args(int ac, char **av)
{
	int (i) = 0;
	if (ac != 2)
		return (ft_putstr_fd(RED BOLD "Usage : ./cub3d <MapPath.cub>\n" RESET,
				2), 1);
	else
	{
		while (av[1][i])
			i++;
		i -= 4;
		if (ft_strncmp(".cub", av[1] + i, 4) != 0)
		{
			ft_putstr_fd(RED BOLD "Invalid map extension, must be .cub\n" RESET,
				2);
			return (1);
		}
	}
	return (0);
}

int	first_char_index(char *line, int i)
{
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

int	find_last_map_element(char *line)
{
	int (i) = ft_strlen(line);
	while (i > 0 && (line[i] != '1' && line[i] == ' ' && line[i] != '0'
			&& line[i] != 'W' && line[i] != 'E' && line[i] != 'S'
			&& line[i] != 'N'))
		i--;
	return (i);
}
