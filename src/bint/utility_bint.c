/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_bint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:16:39 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/15 20:29:17 by yforeau          ###   ########.fr       */
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
	return (BINT_SUCCESS);
}

int		bintcmp(const t_bint l, const t_bint r)
{
	int	i;

	if (BINT_LEN(l) != BINT_LEN(r))
		return (BINT_LEN(l) - BINT_LEN(r));
	i = BINT_LEN(l);
	while (i > 0 && l[i] == r[i])
		--i;
	if (i == 0)
		return (0);
	else
		return (l[i] > r[i] ? 1 : -1);
}

void	bintclr(t_bint b)
{
	while (BINT_LEN(b))
		b[b[0]-- & BINT_LEN_MASK] = 0;
}

void	bintinit(t_bint b, uint32_t size)
{
	size = size ? size : BINT_SIZE_DEF;
	b[0] = size << 16;
	SET_BINT_LEN(b, BINT_SIZE(b) - 1);
	bintclr(b);
}
