/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 20:33:29 by obelouch          #+#    #+#             */
/*   Updated: 2018/10/10 03:52:19 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*current_node;

	if (alst && del)
	{
		while (*alst != NULL)
		{
			current_node = *alst;
			del((*alst)->content, (*alst)->content_size);
			*alst = (*alst)->next;
			free(current_node);
		}
	}
}
