/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:52:55 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/30 15:42:29 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*output;
	t_list	*tmp;
	t_list	*iter;
	void	*new_content;

	if (!f || !del)
		return (0);
	iter = lst;
	output = 0;
	while (iter)
	{
		new_content = f(iter->content);
		tmp = ft_lstnew(new_content);
		if (!tmp)
		{
			del(new_content);
			ft_lstclear(&output, del);
			return (0);
		}
		ft_lstadd_back(&output, tmp);
		iter = iter->next;
	}
	return (output);
}
