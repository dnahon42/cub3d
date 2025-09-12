/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:49:56 by teixeirak         #+#    #+#             */
/*   Updated: 2025/06/26 19:59:56 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1 && (unsigned char)s1[i] == (unsigned char)s2[i]) && (s1[i]
			|| s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
