/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:12:45 by yforeau           #+#    #+#             */
/*   Updated: 2021/07/07 10:29:10 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

static int	internal_bint_mult(t_bint res, const t_bint s,
	const t_bint l, uint32_t limit)
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
	uint32_t	test[BINT_SIZE_DEF] = BINT_DEFAULT(0);

	if ((max = BINT_LEN(l) + BINT_LEN(r)) >= BINT_SIZE_DEF)
		return (BINT_FAILURE);
	if (internal_bint_mult(test, BINT_LEN(l) < BINT_LEN(r) ? l : r,
		BINT_LEN(l) < BINT_LEN(r) ? r : l, BINT_SIZE(test)) == BINT_FAILURE)
		return (BINT_FAILURE);
	SET_BINT_LEN(test, (max > 0 && test[max] == 0 ? max - 1 : max));
	SET_BINT_SIGN(test, BINT_SIGN(l) != BINT_SIGN(r));
	return (bintcpy(res, test));
}
