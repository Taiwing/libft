/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:10:47 by yforeau           #+#    #+#             */
/*   Updated: 2019/03/28 12:06:34 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *elem;

	if ((elem = (t_list *)ft_secmalloc(sizeof(t_list))))
	{
		if (content == NULL)
			elem->content = NULL;
		else
		{
			if (!(elem->content = ft_secmalloc(content_size)))
			{
				free(elem);
				return (NULL);
			}
			ft_memcpy(elem->content, content, content_size);
		}
		elem->content_size = content ? content_size : 0;
		elem->next = NULL;
	}
	return (elem);
}
