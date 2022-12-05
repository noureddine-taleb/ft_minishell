/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:05:08 by ntaleb            #+#    #+#             */
/*   Updated: 2022/08/07 12:45:45 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*el;
	void	*content;

	new = NULL;
	while (lst)
	{
		content = f(lst->content);
		el = ft_lstnew(content);
		if (!el)
		{
			del(content);
			ft_lstclear(&new, del);
			break ;
		}
		else
			ft_lstadd_back(&new, el);
		lst = lst->next;
	}
	return (new);
}
