/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bintset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:55:38 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/16 12:01:28 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

int		bintset_u64(t_bint dst, uint64_t u)
{
	uint32_t	i;

	i = 0;
	while (u)
	{
		if (i == BINT_SIZE(dst) - 1)
			return (BINT_FAILURE);
		dst[++i] = (uint32_t)(u & 0xFFFFFFFF);
		u >>= 32;
	}
	SET_BINT_LEN(dst, i);
	SET_BINT_SIGN(dst, 0);
	return (BINT_SUCCESS);
}

int		bintset_i64(t_bint dst, int64_t i)
{
	if (bintset_u64(dst, i < 0 ? -i : i) == BINT_FAILURE)
		return (BINT_FAILURE);
	SET_BINT_SIGN(dst, i < 0);
	return (BINT_SUCCESS);
}
