/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:30:23 by teixeirak         #+#    #+#             */
/*   Updated: 2025/06/29 18:21:43 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	results_deux;
	char	*buffer;
	size_t	results_un;

	if (!s1 || !s2)
		return (NULL);
	results_un = ft_strlen(s1);
	results_deux = ft_strlen(s2);
	buffer = ft_calloc(results_un + results_deux + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, s1, results_un);
	ft_memcpy(buffer + results_un, s2, results_deux);
	return (buffer);
}

/// // int	main(void)
// {
// 	char	*s1;
// 	char	*s2;
// 	char	*result;
//
// 	s1 = "hello";
// 	s2 = "test";
// 	result = ft_strjoin(s1, s2);
// 	printf("%s\n", result);
// 	free(result);
// }/ // int	main(void)
// {
// 	char	*s1;
// 	char	*s2;
// 	char	*result;
//
// 	s1 = "hello";
// 	s2 = "test";
// 	result = ft_strjoin(s1, s2);
// 	printf("%s\n", result);
// 	free(result);
// }
