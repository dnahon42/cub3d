/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:52:25 by teixeirak         #+#    #+#             */
/*   Updated: 2025/04/28 16:34:52 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Creation d'un block memoire qui me permet de manipuler un noeu je peux
changer son content son next le deplacer et le free independamment*/
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
