/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_bint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:16:39 by yforeau           #+#    #+#             */
/*   Updated: 2021/06/09 13:33:41 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

int			bintcpy(t_bint dst, const t_bint src)
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

void		bintclean(t_bint b)
{
	uint32_t	len;

	for (len = BINT_SIZE(b) - 1; len > BINT_LEN(b); --len)
		b[len] = 0;
	for (; len > 0 && !b[len]; --len);
	SET_BINT_LEN(b, len);
}

void		bintclr(t_bint b)
{
	SET_BINT_LEN(b, 0);
	bintclean(b);
	SET_BINT_SIGN(b, 0);
}

void		bintinit(t_bint b, uint32_t size)
{
	size = size ? size : BINT_SIZE_DEF;
	b[0] = size << 16;
	bintclr(b);
}

uint32_t	bintlog2(t_bint b)
{
	int			log2;
	uint32_t	hi_block;

	if (!BINT_LEN(b))
		return (1);
	log2 = ((BINT_LEN(b) - 1) * 32);
	hi_block = b[BINT_LEN(b)];
	while (hi_block)
	{
		++log2;
		hi_block >>= 1;
	}
	return (log2);
}
