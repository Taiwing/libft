/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shiftleft_bint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:41:15 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/15 20:31:31 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

static void	shift_part(t_bint res, uint32_t shift_blocks, uint32_t shift_bits)
{
	uint32_t	in;
	uint32_t	out;
	uint32_t	low;
	uint32_t	high;
	uint32_t	block;

	in = BINT_LEN(res);
	out = in + shift_blocks + 1;
	SET_BINT_LEN(res, out);
	high = 0;
	block = res[in];
	low = block >> (32 - shift_bits);
	while (in > 1)
	{
		res[out--] = high | low;
		high = block << shift_bits;
		block = res[--in];
		low = block >> (32 - shift_bits);
	}
	res[out] = high | low;
	res[--out] = block << shift_bits;
	while (out > 1)
		res[--out] = 0;
	if (!res[BINT_LEN(res)])
		SET_BINT_LEN(res, BINT_LEN(res) - 1);
}

/*
** Simply shift left res which is equivalent to: res *= 2^shift
*/
int			bint_shiftleft(t_bint res, uint32_t shift)
{
	uint32_t	shift_blocks;
	uint32_t	shift_bits;
	uint32_t	out;
	uint32_t	in;

	if (!shift)
		return (BINT_SUCCESS);
	shift_blocks = shift / 32;
	shift_bits = shift % 32;
	if (BINT_LEN(res) + shift_blocks > BINT_SIZE(res) - 1)
		return (BINT_FAILURE);
	if (!shift_bits)
	{
		in = BINT_LEN(res);
		out = in + shift_blocks;
		while (in > 0)
			res[out--] = res[in--];
		while (out > 0)
			res[out--] = 0;
		SET_BINT_LEN(res, BINT_LEN(res) + shift_blocks);
	}
	else
		shift_part(res, shift_blocks, shift_bits);
	return (BINT_SUCCESS);
}
