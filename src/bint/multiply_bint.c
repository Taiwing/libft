/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_bint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:58:07 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/14 18:30:59 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

int			mult_32bint(t_bint res, t_bint lef, uint32_t rig)
{
	uint32_t	*r;
	uint32_t	*l;
	uint64_t	prod;

	prod = 0;
	r = res + 1;
	l = lef + 1;
	while (l < lef + 1 + (lef[0] & NBR_LENGTH))
	{
		prod += (uint64_t)(*l++) * rig;
		*r++ = (uint32_t)(prod & 0xFFFFFFFF);
		prod >>= 32;
	}
	if (prod)
	{
		if ((lef[0] & NBR_LENGTH) + 1 > ((res[0] & ARR_SIZE) >> 16))
			return (0);
		*r = (uint32_t)prod;
	}
	res[0] = (res[0] & ~NBR_LENGTH) + (lef[0] & NBR_LENGTH) + (prod != 0);
	return (1);
}

int			mult2_bint(t_bint res, t_bint in)
{
	uint32_t	*i;
	uint32_t	*r;
	uint32_t	carry;
	uint32_t	limit;

	i = in;
	r = res;
	carry = 0;
	limit = ((res[0] & ARR_SIZE) >> 16) - 1;
	if (limit < (in[0] & NBR_LENGTH))
		return (0);
	while (++i < in + 1 + (in[0] & NBR_LENGTH))
	{
		*++r = (*i << 1) | carry;
		carry = *i >> 31;
	}
	if (carry)
	{
		if (r - res + 1 > limit)
			return (0);
		*++r = carry;
	}
	res[0] = (res[0] & ~NBR_LENGTH) + (in[0] & NBR_LENGTH) + (carry != 0);
	return (1);
}

int			smult2_bint(t_bint res)
{
	uint32_t	*r;
	uint32_t	cur;
	uint32_t	carry;
	uint32_t	limit;

	r = res;
	carry = 0;
	limit = ((res[0] & ARR_SIZE) >> 16) - 1;
	while (++r < res + 1 + (res[0] & NBR_LENGTH))
	{
		cur = *r;
		*r = (cur << 1) | carry;
		carry = cur >> 31;
	}
	if (carry)
	{
		if (r - res + 1 > limit)
			return (0);
		*r = carry;
		++res[0];
	}
	return (1);
}

int			smult10_bint(t_bint res)
{
	uint32_t	*r;
	uint64_t	prod;

	r = res;
	prod = 0;
	while (++r < res + 1 + (res[0] & NBR_LENGTH))
	{
		prod += (uint64_t)(*r) * 10ull;
		*r = (uint32_t)(prod & 0xFFFFFFFF);
		prod >>= 32;
	}
	if (prod)
	{
		if (r - res + 1 > ((res[0] & ARR_SIZE) >> 16) - 1)
			return (0);
		*r = (uint32_t)prod;
		++res[0];
	}
	return (1);
}
