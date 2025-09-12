/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_lstadd_front.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:00:18 by kiteixei          #+#    #+#             */
/*   Updated: 2025/04/28 18:40:57 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// New pointe sur l'ancien debut de la liste
// tu met new en tant que nouveau premier element de la liste
// Je deplace juste des liens donc pas besoin de malloc
// [list] --> [deuxieme] --> [premiere] --> [NULL];
// je verifie si la lst et le new sont vide 
// lst est un pointeur sur pointeur (je modifie la tete de liste
//new est le nouveau maillon a ajouter en tete
// d'abord tu relies new a l'ancienne list ensuite je pointe lst vers new 
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include "libft.h"
#include <stdio.h>

int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*tmp;
	t_list	*next;

	t_list *head = NULL; // liste vide
	node1 = ft_lstnew("Premier");
	node2 = ft_lstnew("Deuxeeeième");
	node3 = ft_lstnew("Troisième");
	// Ajout des maillons un par un
	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	ft_lstadd_front(&head, node3);
	// parcourir la liste pour afficher le conte
	tmp = head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	// free la memoire
	tmp = head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	return (0);
}
*/
