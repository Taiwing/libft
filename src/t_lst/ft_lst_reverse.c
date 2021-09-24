/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 01:45:13 by yforeau           #+#    #+#             */
/*   Updated: 2021/09/24 17:43:32 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef THREAD_SAFE
VOID_MUTEXIFY(ft_lst_reverse, t_list**, lst)
#else
void	ft_lst_reverse(t_list **lst)
#endif
{
	static t_list	*prev = 0;
	t_list			*next;

	if (!lst || !*lst)
		return ;
	next = (*lst)->next;
	(*lst)->next = prev;
	prev = *lst;
	if (next)
#ifdef THREAD_SAFE
		ts_ft_lst_reverse(&next);
#else
		ft_lst_reverse(&next);
#endif
	if (!(*lst)->next)
	{
		*lst = prev;
		prev = 0;
	}
}
