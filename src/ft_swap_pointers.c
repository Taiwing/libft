/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_pointers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:58:26 by yforeau           #+#    #+#             */
/*   Updated: 2019/01/23 18:05:09 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

/*
** This function takes two double pointers casted with (uintptr_t *).
** It swaps their value without temporary variable (yeah, thats pretty cool).
*/

void	ft_swap_pointers(uintptr_t *p1, uintptr_t *p2)
{
	*p1 ^= *p2;
	*p2 ^= *p1;
	*p1 ^= *p2;
}
