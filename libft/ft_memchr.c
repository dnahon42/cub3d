/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teixeirakillian <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:48:11 by teixeirak         #+#    #+#             */
/*   Updated: 2025/03/04 16:48:14 by teixeirak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*d = (const unsigned char *)s;
	const unsigned char	uc = (unsigned char)c;

	while (n--)
	{
		if (*d == uc)
			return ((void *)d);
		d++;
	}
	return (NULL);
}
