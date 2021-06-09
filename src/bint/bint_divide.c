/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_divide.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:22:38 by yforeau           #+#    #+#             */
/*   Updated: 2021/06/08 19:29:38 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

/*
** Divide dividend by divisor, return the quotient and the remainder where:
** quotient = floor(dividend/divisor)
** remainder = dividend - (divisor * floor(dividend/divisor))
**
** quotient can be NULL if we dont need it
*/
int	bint_divmod(t_bint quotient, t_bint remainder,
	const t_bint dividend, const t_bint divisor)
{
	if (!remainder)
		return (BINT_FAILURE);
	if (bint_divide(quotient, remainder, dividend, divisor) == BINT_FAILURE)
		return (BINT_FAILURE);
	if (BINT_SIGN(dividend) == BINT_SIGN(divisor) || !BINT_LEN(remainder))
		return (BINT_SUCCESS);
	if (quotient)
		bint_sub_u64(quotient, quotient, 1);
	bint_add(remainder, remainder, divisor);
	return (BINT_SUCCESS);
}

static int	base_case_divide(t_bint quotient, t_bint remainder,
	const t_bint dividend, const t_bint divisor)
{
	int			ret = BINT_SUCCESS;
	int			(*rop)(t_bint, t_bint, t_bint) = bint_sub;
	int			(*qop)(t_bint, t_bint, uint64_t) = bint_add_u64;

	rop = BINT_SIGN(dividend) != BINT_SIGN(divisor) ? bint_add : rop;
	qop = BINT_SIGN(dividend) != BINT_SIGN(divisor) ? bint_sub_u64 : qop;
	while (bintcmp_abs(remainder, divisor) >= 0 && ret == BINT_SUCCESS)
	{
		ret = rop(remainder, remainder, divisor);
		if (quotient && ret == BINT_SUCCESS)
			ret = qop(quotient, quotient, 1);
	}
	return (ret);
}

/*
** Divide dividend by divisor, return the quotient and the remainder where:
** quotient = dividend/divisor = quotient > 0 ? floor(quotient) : ceil(quotient)
** remainder = dividend - (divisor * quotient)
**
** quotient or remainder can be NULL if we dont need one or the other
*/
int	bint_divide(t_bint quotient, t_bint remainder,
	const t_bint dividend, const t_bint divisor)
{
	uint32_t	local_remainder[BINT_SIZE_DEF];

	if (!BINT_LEN(divisor) || (!quotient && !remainder))
		return (BINT_FAILURE);
	if (!remainder)
	{
		bintinit(local_remainder, 0);
		remainder = local_remainder;
	}
	if (bintcpy(remainder, dividend) == BINT_FAILURE)
		return (BINT_FAILURE);
	if (quotient)
		bintclr(quotient);
	return (base_case_divide(quotient, remainder, dividend, divisor));
}
