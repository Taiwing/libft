/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pow_bint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:26:58 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/14 22:38:10 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"
#include "bint_mathconsts.h"

/*
** Compute 10^exp and put it into res, with: exp <= (2^13)-1
** So exp <= 8191 (wich is: 2^0+2^1+2^2+2^3+...+2^11+2^12)
*/
int		pow10_bint(t_bint res, uint32_t exp)
{
	uint32_t	i;
	uint32_t	cur[BINT_SIZE];
	uint32_t	next[BINT_SIZE];

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
			if (!mult_bint(next, cur, (t_bint)g_pow10_big[i])
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
int		multpow10_bint(t_bint res, t_bint in, uint32_t exp)
{
	uint32_t	tmp[BINT_SIZE];

	bintinit(tmp, 0);
	return (pow10_bint(tmp, exp) && mult_bint(res, tmp, in));
}

/*
** Compute 2^exp and put it into res
** exp is only limited by UINT32_MAX and ARR_SIZE
*/
int		pow2_bint(t_bint res, uint32_t exp)
{
	uint32_t	i;
	uint32_t	index;

	index = exp / 32;
	if (index > ((res[0] & ARR_SIZE) >> 16) - 1)
		return (0);
	i = 0;
	while (++i <= index + 1)
		res[i] = 0;
	res[index + 1] |= 1 << (exp % 32);
	res[0] = (res[0] & ~NBR_LENGTH) + index + 1;
	return (1);
}
