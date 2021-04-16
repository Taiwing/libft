/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 12:27:08 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/16 13:11:38 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

/*
** Add rig to res and put the result in res without considering the sign
*/
int			bint_sadd_u32_abs(t_bint res, uint32_t rig)
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

static int	internal_bint_add(t_bint res, const t_bint small,
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
** Add l to r and put the result in res without considering the sign
*/
int			bint_add_abs(t_bint res, const t_bint l, const t_bint r)
{
	uint32_t	max;

	max = BINT_LEN(l) > BINT_LEN(r) ? BINT_LEN(l) : BINT_LEN(r);
	if (max > BINT_SIZE(res) - 1)
		return (BINT_FAILURE);
	bintclr(res);
	if (!internal_bint_add(res, BINT_LEN(l) < BINT_LEN(r) ? l : r,
			BINT_LEN(l) < BINT_LEN(r) ? r : l, max))
		return (BINT_FAILURE);
	return (BINT_SUCCESS);
}

/*
** Add l to r and put the result in res without considering the sign
*/
int			bint_add(t_bint res, const t_bint l, const t_bint r)
{
	int	cmp;

	if (BINT_SIGN(l) == BINT_SIGN(r))
	{
		if (bint_add_abs(res, l, r) == BINT_FAILURE)
			return (BINT_FAILURE);
		SET_BINT_SIGN(res, BINT_SIGN(l));
		return (BINT_SUCCESS);
	}
	else if (!(cmp = bintcmp_abs(l, r)))
	{
		bintclr(res);
		return (BINT_SUCCESS);
	}
	//TODO: uncomment when bint_sub will be implemented
	/*
	else if (bint_sub_abs(res, l, r) == BINT_FAILURE)
		return (BINT_FAILURE);
	SET_BINT_SIGN(res, cmp > 0 ? BINT_SIGN(l) : BINT_SIGN(r));
	*/
	return (BINT_SUCCESS);
}
