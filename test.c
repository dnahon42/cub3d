/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:03:00 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/17 20:04:56 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_bit(char octet)
{
	char	stock;
	int		i;

	i = 7;
	while (i <= 8)
	{
		stock = octet << 1 + '0';
		write(1, &stock, 1);
		i++;
	}
}
int	main(void)
{
	ft_print_bit(1);
}
