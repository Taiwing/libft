/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:15:59 by yforeau           #+#    #+#             */
/*   Updated: 2021/05/12 14:22:49 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

/*
** Substract rig from res, or res from rig and put the result in res without
** considering the sign. The smallest value is always gonna be substracted
** from the biggest one.
*/
int			bint_ssub_u32_abs(t_bint res, uint32_t rig)
{
	uint32_t	*r;
	uint32_t	carry;

	r = res;
	carry = 0;
	if (BINT_LEN(res) == 1 && rig >= r[1])
		r[1] = rig - r[1];
	else
		carry = rig;
	while (carry && ++r < res + 1 + BINT_LEN(res))
	{
		carry = rig > *r;
		*r = carry ? 0xFFFFFFFF - (rig - *r - 1) : *r - rig;
		rig = carry;
	}
	if (BINT_LEN(res) && !res[BINT_LEN(res)])
		SET_BINT_LEN(res, BINT_LEN(res) - 1);
	return (BINT_SUCCESS);
}

static void	internal_bint_sub(t_bint res, const t_bint small,
	const t_bint large)
{
	uint32_t	i;
	uint64_t	diff;

	diff = 0;
	for (i = 1; i <= BINT_LEN(large); ++i)
	{
		if (i <= BINT_LEN(small))
			diff = (uint64_t)large[i] - (uint64_t)small[i] - diff;
		else
			diff = (uint64_t)large[i] - diff;
		res[i] = diff & 0xFFFFFFFF;
		diff = (diff >> 32) & 1;
	}
	SET_BINT_LEN(res, BINT_LEN(large));
	while (BINT_LEN(res) && !res[BINT_LEN(res)])
		SET_BINT_LEN(res, BINT_LEN(res) - 1);
}

/*
** Substract r from l, or l from r and put the result in res without
** considering the sign. The smallest value is always gonna be substracted
** from the biggest one.
*/
int			bint_sub_abs(t_bint res, const t_bint l, const t_bint r)
{
	int	cmp;

	if (BINT_LEN(l) > BINT_SIZE(res) - 1 || BINT_LEN(r) > BINT_SIZE(res) - 1)
		return (BINT_FAILURE);
	bintclr(res);
	if ((cmp = bintcmp_abs(l, r)))
		internal_bint_sub(res, cmp < 0 ? l : r, cmp < 0 ? r : l);
	return (BINT_SUCCESS);
}

/*
** Substract r from l and put the result in res
*/
int			bint_sub(t_bint res, const t_bint l, const t_bint r)
{
	int	cmp;

	if (BINT_SIGN(l) == BINT_SIGN(r))
	{
		if (!(cmp = bintcmp_abs(l, r)))
		{
			bintclr(res);
			return (BINT_SUCCESS);
		}
		else if (bint_sub_abs(res, l, r) == BINT_FAILURE)
			return (BINT_FAILURE);
		SET_BINT_SIGN(res, cmp > 0 ? BINT_SIGN(l) : !BINT_SIGN(r));
		return (BINT_SUCCESS);
	}
	else if (bint_add_abs(res, l, r) == BINT_FAILURE)
		return (BINT_FAILURE);
	SET_BINT_SIGN(res, BINT_SIGN(l));
	return (BINT_SUCCESS);
}
