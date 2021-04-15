/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pow_bint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:26:58 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/15 10:51:46 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"
#include "bint_mathconsts.h"

/*
** Compute 10^exp and put it into res, with: exp <= (2^13)-1
** So exp <= 8191 (wich is: 2^0+2^1+2^2+2^3+...+2^11+2^12)
*/
int		bint_pow10(t_bint res, uint32_t exp)
{
	uint32_t	i;
	uint32_t	cur[BINT_SIZE_DEF];
	uint32_t	next[BINT_SIZE_DEF];

	if (exp >> 13)
		return (0);
	bintinit(cur, 0);
	bintinit(next, 0);
	if (!bintset(g_pow10_u32[exp & 0x7], cur))
		return (0);
	exp >>= 3;
	i = 0;
	while (exp)
	{
		if (exp & 1)
		{
			if (!bint_mult(next, cur, (t_bint)g_pow10_big[i])
				|| !bintcpy(next, cur))
				return (0);
		}
		++i;
		exp >>= 1;
	}
	return (bintcpy(cur, res));
}

/*
** Multiply in to 10^exp and put it into res
*/
int		bint_multpow10(t_bint res, t_bint in, uint32_t exp)
{
	uint32_t	tmp[BINT_SIZE_DEF];

	bintinit(tmp, 0);
	return (bint_pow10(tmp, exp) && bint_mult(res, tmp, in));
}

/*
** Compute 2^exp and put it into res
** exp is only limited by UINT32_MAX and BINT_SIZE
*/
int		bint_pow2(t_bint res, uint32_t exp)
{
	uint32_t	i;
	uint32_t	index;

	index = exp / 32;
	if (index > BINT_SIZE(res) - 1)
		return (0);
	i = 0;
	while (++i <= index + 1)
		res[i] = 0;
	res[index + 1] |= 1 << (exp % 32);
	SET_BINT_LEN(res, index + 1);
	return (1);
}
