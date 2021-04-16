/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bintset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:55:38 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/16 13:24:56 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"
#include "bint_mathconsts.h"

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

/*
** Compute 2^exp and put it into res
** exp is only limited by UINT32_MAX and BINT_SIZE
*/
int		bintset_pow2(t_bint res, uint32_t exp)
{
	uint32_t	i;
	uint32_t	index;

	index = exp / 32;
	if (index > BINT_SIZE(res) - 1)
		return (BINT_FAILURE);
	i = 0;
	while (++i <= index + 1)
		res[i] = 0;
	res[index + 1] |= 1 << (exp % 32);
	SET_BINT_LEN(res, index + 1);
	return (BINT_SUCCESS);
}

/*
** Compute 10^exp and put it into res, with: exp <= (2^13)-1
** So exp <= 8191 (wich is: 2^0+2^1+2^2+2^3+...+2^11+2^12)
*/
int		bintset_pow10(t_bint res, uint32_t exp)
{
	uint32_t	i;
	uint32_t	cur[BINT_SIZE_DEF];
	uint32_t	next[BINT_SIZE_DEF];

	if (exp >> 13)
		return (BINT_FAILURE);
	bintinit(cur, 0);
	bintinit(next, 0);
	if (bintset_u64(cur, (uint64_t)g_pow10_u32[exp & 0x7]) == BINT_FAILURE)
		return (BINT_FAILURE);
	exp >>= 3;
	i = 0;
	while (exp)
	{
		if (exp & 1)
		{
			if (bint_mult(next, cur, (t_bint)g_pow10_big[i]) == BINT_FAILURE
				|| bintcpy(cur, next) == BINT_FAILURE)
				return (BINT_FAILURE);
		}
		++i;
		exp >>= 1;
	}
	return (bintcpy(res, cur));
}
