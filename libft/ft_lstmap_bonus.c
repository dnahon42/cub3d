/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:50:53 by teixeirak         #+#    #+#             */
/*   Updated: 2025/04/29 10:50:54 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Tu lis chaque element tu le transforme tu fais un nouveau maillon avec
// le resultat et tu construis une nouvelle liste
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_elem = ft_lstnew(new_content);
		if (!new_elem)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *map_function(void *content)
{
    char *str = (char *)content;
    char *new_str = malloc(ft_strlen(str) + 2);     
	if (!new_str)
        return (NULL);
    ft_strcpy(new_str, str);
    ft_strcat(new_str, "!");
    return (new_str);
}

void del_function(void *content)
{
    free(content);
}

int main(void)
{
    t_list *original;
    t_list *mapped;
    t_list *tmp;
    original = ft_lstnew(strdup("Salut"));
    original->next = ft_lstnew(strdup("Comment"));
    original->next->next = ft_lstnew(strdup("Ca va"));

    mapped = ft_lstmap(original, &map_function, &del_function);

    printf("Liste originale :\n");
    tmp = original;
    while (tmp)
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }

    printf("\nListe mappée :\n");
    tmp = mapped;
    while (tmp)
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }

    ft_lstclear(&original, &del_function);
    ft_lstclear(&mapped, &del_function);

    return (0);
}
*/
