/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 14:20:22 by yforeau           #+#    #+#             */
/*   Updated: 2021/06/26 14:26:36 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

int	bint_is_odd(const t_bint b)
{
	return (BINT_LEN(b) && (b[1] & 1));
}

int	bint_is_even(const t_bint b)
{
	return (!bint_is_odd(b));
}
