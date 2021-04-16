/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_bint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:16:39 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/16 11:46:03 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

int		bintcpy(t_bint dst, const t_bint src)
{
	uint32_t	i;

	if (BINT_LEN(src) > BINT_SIZE(dst) - 1)
		return (BINT_FAILURE);
	i = 0;
	while (i < BINT_LEN(src))
	{
		++i;
		dst[i] = src[i];
	}
	SET_BINT_LEN(dst, i);
	SET_BINT_SIGN(dst, BINT_SIGN(src));
	return (BINT_SUCCESS);
}

int		bintset(t_bint dst, uint64_t u)
{
	uint32_t	i;

	i = 0;
	while (u)
	{
		if (i == BINT_SIZE(dst) - 1)
			return (BINT_FAILURE);
		dst[++i] = (uint32_t)(u & 0xFFFFFFFF);
		u >>= 32;
	}
	SET_BINT_LEN(dst, i);
	SET_BINT_SIGN(dst, 0);
	return (BINT_SUCCESS);
}

void	bintclr(t_bint b)
{
	while (BINT_LEN(b))
		b[b[0]-- & BINT_LEN_MASK] = 0;
	SET_BINT_SIGN(b, 0);
}

void	bintinit(t_bint b, uint32_t size)
{
	size = size ? size : BINT_SIZE_DEF;
	b[0] = size << 16;
	SET_BINT_LEN(b, BINT_SIZE(b) - 1);
	bintclr(b);
}
