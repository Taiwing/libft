/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 16:20:05 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/15 20:07:02 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

/*
** Add rig to res and put the result in res
*/
int			bint_sadd_u32(t_bint res, uint32_t rig)
{
	uint32_t	*r;
	uint64_t	sum;

	r = res;
	sum = rig;
	while (sum && ++r < res + 1 + BINT_LEN(res))
	{
		sum += (uint64_t)(*r);
		*r = (uint32_t)(sum & 0xFFFFFFFF);
		sum >>= 32;
	}
	if (sum)
	{
		if (BINT_LEN(res) + 1 > BINT_SIZE(res) - 1)
			return (BINT_FAILURE);
		*r = (uint32_t)sum;
		SET_BINT_LEN(res, BINT_LEN(res) + 1);
	}
	return (BINT_SUCCESS);
}

static int	add(t_bint res, const t_bint small,
	const t_bint large, uint32_t max)
{
	uint64_t		sum;
	uint32_t		*r;
	const uint32_t	*c;
	const uint32_t	*l;

	sum = 0;
	r = res;
	c = small;
	l = large;
	while (++c < small + 1 + BINT_LEN(small))
	{
		sum += (uint64_t)(*++l) + *c;
		*++r = sum & 0xFFFFFFFF;
		sum >>= 32;
	}
	while (++l < large + 1 + BINT_LEN(large))
	{
		sum += (uint64_t)(*l);
		*++r = sum & 0xFFFFFFFF;
		sum >>= 32;
	}
	if (sum == 1 && max < BINT_SIZE(res) - 1)
		*++r = 1;
	SET_BINT_LEN(res, max + sum);
	return (!sum || (sum == 1 && max < BINT_SIZE(res) - 1));
}

/*
** Add l to r and put the result in res
*/
int			bint_add(t_bint res, const t_bint l, const t_bint r)
{
	uint32_t	max;

	max = BINT_LEN(l) > BINT_LEN(r) ? BINT_LEN(l) : BINT_LEN(r);
	if (max > BINT_SIZE(res) - 1)
		return (BINT_FAILURE);
	bintclr(res);
	if (!add(res, BINT_LEN(l) < BINT_LEN(r) ? l : r,
			BINT_LEN(l) < BINT_LEN(r) ? r : l, max))
		return (BINT_FAILURE);
	return (BINT_SUCCESS);
}

static int	mult(t_bint res, const t_bint s, const t_bint l, uint32_t limit)
{
	uint64_t	prod;
	uint32_t	i;
	uint32_t	j;

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
		res++;
	}
	return (BINT_SUCCESS);
}

/*
** Multiply l by r and put the result in res
*/
int			bint_mult(t_bint res, const t_bint l, const t_bint r)
{
	uint32_t	max;

	max = BINT_LEN(l) + BINT_LEN(r);
	if (l == res || r == res || max > BINT_SIZE_DEF - 1)
		return (BINT_FAILURE);
	bintclr(res);
	if (mult(res, BINT_LEN(l) < BINT_LEN(r) ? l : r,
		BINT_LEN(l) < BINT_LEN(r) ? r : l, BINT_SIZE(res)) == BINT_FAILURE)
		return (BINT_FAILURE);
	SET_BINT_LEN(res, (max > 0 && res[max] == 0 ? max - 1 : max));
	return (BINT_SUCCESS);
}
