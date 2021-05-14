/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 12:27:08 by yforeau           #+#    #+#             */
/*   Updated: 2021/05/14 15:42:11 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

static int	internal_bint_add(t_bint res, const t_bint small,
	const t_bint large)
{
	uint32_t	i;
	uint64_t	sum;

	sum = 0;
	for (i = 1; i <= BINT_LEN(large); ++i)
	{
		if (i <= BINT_LEN(small))
			sum += (uint64_t)large[i] + (uint64_t)small[i];
		else
			sum += (uint64_t)large[i];
		res[i] = sum & 0xFFFFFFFF;
		sum >>= 32;
	}
	if (sum && i >= BINT_SIZE(res))
		return (BINT_FAILURE);
	else if (sum)
		res[i] = sum;
	SET_BINT_LEN(res, i - (!sum));
	bintclean(res);
	return (BINT_SUCCESS);
}

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

/*
** Add l to r and put the result in res without considering the sign
*/
int			bint_add_abs(t_bint res, const t_bint l, const t_bint r)
{
	t_bint		small;
	t_bint		large;

	small = BINT_LEN(l) > BINT_LEN(r) ? r : l;
	large = BINT_LEN(l) > BINT_LEN(r) ? l : r;
	return (internal_bint_add(res, small, large));
}

/*
** Add l to r and put the result in res
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
	else if (bint_sub_abs(res, l, r) == BINT_FAILURE)
		return (BINT_FAILURE);
	SET_BINT_SIGN(res, cmp > 0 ? BINT_SIGN(l) : BINT_SIGN(r));
	return (BINT_SUCCESS);
}
