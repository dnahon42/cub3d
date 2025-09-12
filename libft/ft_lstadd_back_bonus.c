/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:57:19 by kiteixei          #+#    #+#             */
/*   Updated: 2025/04/29 13:45:19 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// La difference entre add back et add front c'est que je respecte
// l'ordre d'ajout.
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p_last;

	if (lst)
	{
		if ((*lst) == NULL)
			*lst = new;
		else
		{
			p_last = ft_lstlast(*lst);
			p_last->next = new;
		}
	}
}
