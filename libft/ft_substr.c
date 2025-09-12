/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:08:40 by teixeirak         #+#    #+#             */
/*   Updated: 2025/04/28 22:20:36 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buffer;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	buffer = (char *)malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, s + start, len);
	buffer[len] = '\0';
	return (buffer);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
char *ft_substr(char const *s, unsigned int start, size_t len); 
int main(void)
{
    char *s = "Hello, world!";
    char *sub;
    
    sub = ft_substr(s, 7, 5); 
    if (sub)
    {
        printf("Substr (7,5) : \"%s\"\n", sub);
        free(sub);
    }

    sub = ft_substr(s, 20, 5); 
    if (sub)
    {
        printf("Substr (20,5) : \"%s\"\n", sub);
        free(sub);
    }

    sub = ft_substr(s, 5, 50); 
    if (sub)
    {
        printf("Substr (5,50) : \"%s\"\n", sub);
        free(sub);
    }

    sub = ft_substr(s, 0, 13); 
    if (sub)
    {
        printf("Substr (0,13) : \"%s\"\n", sub);
        free(sub);
    }

    return (0);
}
*/
