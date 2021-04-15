/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_bint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:58:07 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/15 11:36:27 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

/*
** Multiply lef by rig and put the result in res
*/
int			bint_mult_u32(t_bint res, t_bint lef, uint32_t rig)
{
	uint32_t	*r;
	uint32_t	*l;
	uint64_t	prod;

	prod = 0;
	r = res + 1;
	l = lef + 1;
	while (l < lef + 1 + BINT_LEN(lef))
	{
		prod += (uint64_t)(*l++) * rig;
		*r++ = (uint32_t)(prod & 0xFFFFFFFF);
		prod >>= 32;
	}
	if (prod)
	{
		if (BINT_LEN(lef) + 1 > BINT_SIZE(res))
			return (BINT_FAILURE);
		*r = (uint32_t)prod;
	}
	SET_BINT_LEN(res, BINT_LEN(lef) + (prod != 0));
	return (BINT_SUCCESS);
}

/*
** Multiply in by 2 and put the result in res
*/
int			bint_mult2(t_bint res, t_bint in)
{
	uint32_t	*i;
	uint32_t	*r;
	uint32_t	carry;
	uint32_t	limit;

	i = in;
	r = res;
	carry = 0;
	limit = BINT_SIZE(res) - 1;
	if (limit < BINT_LEN(in))
		return (BINT_FAILURE);
	while (++i < in + 1 + BINT_LEN(in))
	{
		*++r = (*i << 1) | carry;
		carry = *i >> 31;
	}
	if (carry)
	{
		if (r - res + 1 > limit)
			return (BINT_FAILURE);
		*++r = carry;
	}
	SET_BINT_LEN(res, BINT_LEN(in) + (carry != 0));
	return (BINT_SUCCESS);
}

/*
** Multiply res by 2 and put the result in res
*/
int			bint_smult2(t_bint res)
{
	uint32_t	*r;
	uint32_t	cur;
	uint32_t	carry;
	uint32_t	limit;

	r = res;
	carry = 0;
	limit = BINT_SIZE(res) - 1;
	while (++r < res + 1 + BINT_LEN(res))
	{
		cur = *r;
		*r = (cur << 1) | carry;
		carry = cur >> 31;
	}
	if (carry)
	{
		if (r - res + 1 > limit)
			return (BINT_FAILURE);
		*r = carry;
		++res[0];
	}
	return (BINT_SUCCESS);
}

/*
** Multiply res by 10 and put the result in res
*/
int			bint_smult10(t_bint res)
{
	uint32_t	*r;
	uint64_t	prod;

	r = res;
	prod = 0;
	while (++r < res + 1 + BINT_LEN(res))
	{
		prod += (uint64_t)(*r) * 10ull;
		*r = (uint32_t)(prod & 0xFFFFFFFF);
		prod >>= 32;
	}
	if (prod)
	{
		if (r - res + 1 > BINT_SIZE(res) - 1)
			return (BINT_FAILURE);
		*r = (uint32_t)prod;
		++res[0];
	}
	return (BINT_SUCCESS);
}
