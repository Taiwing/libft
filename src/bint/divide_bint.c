/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_bint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:00:29 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/14 18:28:37 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

static void	substract_bintxu32(t_bint res, t_bint b, uint32_t q)
{
	uint32_t	i;
	uint64_t	prod;
	uint64_t	diff;

	i = 0;
	prod = 0;
	diff = 0;
	while (++i <= (b[0] & NBR_LENGTH))
	{
		prod += (uint64_t)b[i] * (uint64_t)q;
		diff = (uint64_t)res[i] - (prod & 0xFFFFFFFF) - diff;
		res[i] = diff & 0xFFFFFFFF;
		prod >>= 32;
		diff = (diff >> 32) & 1;
	}
	while ((res[0] & NBR_LENGTH) > 1 && !res[res[0] & NBR_LENGTH])
		--res[0];
}

uint32_t		divmod_max9_bint(t_bint dividend, t_bint divisor)
{
	uint32_t	quotient;

	if (!(divisor[0] & NBR_LENGTH) || divisor[divisor[0] & NBR_LENGTH] < 8
		|| divisor[divisor[0] & NBR_LENGTH] > 0xFFFFFFFE
		|| (dividend[0] & NBR_LENGTH) > (divisor[0] & NBR_LENGTH))
		return (10);
	if ((divisor[0] & NBR_LENGTH) > (dividend[0] & NBR_LENGTH))
		return (0);
	quotient = dividend[dividend[0] & NBR_LENGTH]
			/ ((divisor[divisor[0] & NBR_LENGTH]) + 1);
	if (quotient)
		substract_bintxu32(dividend, divisor, quotient);
	if (bintcmp(dividend, divisor) >= 0)
	{
		++quotient;
		substract_bintxu32(dividend, divisor, 1);
	}
	return (quotient);
}
