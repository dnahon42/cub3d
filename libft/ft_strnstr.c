/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:19:03 by teixeirak         #+#    #+#             */
/*   Updated: 2025/04/28 22:01:34 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* je chercher une sous chaine (needle) dans une autre chaine (haystack) mais 
seulement dnas les len premiers caractere de haystack*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] && haystack[i + j] == needle[j]
			&& (i + j) < len)
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *haystack = "Salut les amis";
    const char *needle = "les";
    size_t len = 10;

    char *res = ft_strnstr(haystack, needle, len);

    if (res)
        printf("Trouvé : \"%s\"\n", res);
    else
        printf("Pas trouvé\n");

    return (0);
}
*/
