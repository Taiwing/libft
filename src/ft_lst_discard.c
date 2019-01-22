/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_discard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:21:10 by yforeau           #+#    #+#             */
/*   Updated: 2019/01/22 18:23:46 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_discard(t_list *prev, t_list **alst)
{
	t_list	*next;

	if (!alst || !*alst)
		return ;
	next = (*alst)->next;
	free((*alst)->content);
	free(*alst);
	*alst = next;
	if (prev)
		prev->next = next;
}
