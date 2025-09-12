/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:37:14 by kiteixei          #+#    #+#             */
/*   Updated: 2025/04/28 22:57:57 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// compter le nombre de noeu dans une list
int	ft_lstsize(t_list *lst)
{
	int		lenlist;

	lenlist = 0;
	while (lst)
	{
		lst = lst->next;
		lenlist++;
	}
	return (lenlist);
}
/*
int main(void)
{
t_list *l;
 	int actual;
 	int expected;
 
 	l = ft_lstnew(ft_strdup("1"));
 	l->next = ft_lstnew(ft_strdup("2"));
 	l->next->next = ft_lstnew(ft_strdup("3"));
 	expected = 3;
 	actual = ft_lstsize(l);
	printf("%d\n",actual);
	if (actual == expected)
		exit(5);
	exit(8);
}
*/
