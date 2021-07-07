/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:12:45 by yforeau           #+#    #+#             */
/*   Updated: 2021/07/07 17:21:02 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

/*
** Standard multiplication algorithm
*/
static int	long_multiplication(t_bint res, const t_bint s,
	const t_bint l, uint32_t limit)
{
	uint64_t	prod;
	uint32_t	i;
	uint32_t	j;

	// TODO: check that it takes less time with this than
	// with BINT_DEFAULT macro
	/*
	for (uint32_t k = 1; k <= BINT_LEN(l); ++k)
		res[k] = 0;
	*/
	i = 0;
	while (++i <= BINT_LEN(s))
	{
		if (s[i])
		{
			j = 0;
			prod = 0;
			while (++j <= BINT_LEN(l))
			{
				prod += res[j] + (l[j] * (uint64_t)s[i]);
				res[j] = prod & 0xFFFFFFFF;
				prod >>= 32;
			}
			if (j >= limit)
				return (BINT_FAILURE);
			res[j] = (uint32_t)(prod & 0xFFFFFFFF);
		}
		++res;
	}
	return (BINT_SUCCESS);
}

static int	bint_split_at(t_bint high, t_bint low,
	const t_bint orig, uint32_t at)
{
	if (at > BINT_LEN(orig) || at >= BINT_SIZE(low)
		|| BINT_LEN(orig) - at >= BINT_SIZE(high))
		return (BINT_FAILURE);
	bintclr(low);
	bintclr(high);
	if (at == BINT_LEN(orig))
		return (bintcpy(low, orig));
	SET_BINT_LEN(low, at);
	SET_BINT_LEN(high, BINT_LEN(orig) - at);
	for (uint32_t i = 1; i <= at; ++i)
		low[i] = orig[i];
	for (uint32_t i = at + 1; i <= BINT_LEN(orig); ++i)
		high[i - at] = orig[i];
	return (BINT_SUCCESS);
}

static int	karatsuba_result(t_bint res,
	uint32_t z[3][BINT_SIZE_DEF], uint32_t m)
{
	if (bint_sub(z[1], z[1], z[2]) == BINT_FAILURE
		|| bint_sub(z[1], z[1], z[0]) == BINT_FAILURE
		|| bint_shiftleft(z[1], m * 32) == BINT_FAILURE
		|| bint_shiftleft(z[2], m * 2 * 32) == BINT_FAILURE
		|| bint_add(z[1], z[0], z[1]) == BINT_FAILURE
		|| bint_add(res, z[1], z[2]) == BINT_FAILURE)
		return (BINT_FAILURE);
	return (BINT_SUCCESS);
}

/*
** Karatsuba multiplication algorithm: recursive divide and conquer
*/
static int	karatsuba(t_bint res, const t_bint s, const t_bint l)
{
	uint32_t	high[2][BINT_SIZE_DEF] = { [ 0 ... 1 ] = BINT_DEFAULT(0) };
	uint32_t	low[2][BINT_SIZE_DEF] = { [ 0 ... 1 ] = BINT_DEFAULT(0) };
	uint32_t	z[3][BINT_SIZE_DEF] = { [ 0 ... 2 ] = BINT_DEFAULT(0) };
	int			cmp;
	uint32_t	m;

	if (BINT_LEN(l) < 10 || BINT_LEN(s) < 2)
		return (long_multiplication(res, s, l, BINT_SIZE(res)));
	m = (BINT_LEN(s) / 2) + (BINT_LEN(s) % 2);
	if (bint_split_at(high[0], low[0], s, m) == BINT_FAILURE
		|| bint_split_at(high[1], low[1], l, m) == BINT_FAILURE)
		return (BINT_FAILURE);
	cmp = bintcmp_abs(low[1], low[0]);
	if (karatsuba(z[0], low[cmp <= 0], low[cmp > 0]) == BINT_FAILURE)
		return (BINT_FAILURE);
	if (karatsuba(z[2], high[0], high[1]) == BINT_FAILURE)
		return (BINT_FAILURE);
	if (bint_add_abs(low[0], low[0], high[0]) == BINT_FAILURE
		|| bint_add_abs(low[1], low[1], high[1]) == BINT_FAILURE)
		return (BINT_FAILURE);
	cmp = bintcmp_abs(low[1], low[0]);
	if (karatsuba(z[1], low[cmp <= 0], low[cmp > 0]) == BINT_FAILURE)
		return (BINT_FAILURE);
	return (karatsuba_result(res, z, m));
}

/*
** Multiply l by r and put the result in res
*/
int			bint_mult(t_bint res, const t_bint l, const t_bint r)
{
	int				cmp;
	uint32_t		max;
	t_bint			small;
	t_bint			large;
	uint32_t		tmp[BINT_SIZE_DEF] = BINT_DEFAULT(0);

	if ((max = BINT_LEN(l) + BINT_LEN(r)) >= BINT_SIZE_DEF)
		return (BINT_FAILURE);
	cmp = bintcmp_abs(l, r);
	small = cmp < 0 ? l : r;
	large = cmp >= 0 ? l : r;
	if (long_multiplication(tmp, small, large, BINT_SIZE(tmp)) == BINT_FAILURE)
		return (BINT_FAILURE);
	/*
	if (karatsuba(tmp, small, large) == BINT_FAILURE)
		return (BINT_FAILURE);
	*/
	SET_BINT_LEN(tmp, (max > 0 && tmp[max] == 0 ? max - 1 : max));
	SET_BINT_SIGN(tmp, BINT_SIGN(l) != BINT_SIGN(r));
	return (bintcpy(res, tmp));
}
