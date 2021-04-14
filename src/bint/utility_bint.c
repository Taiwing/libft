/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_bint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:16:39 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/14 18:34:38 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bint.h"

int		bintcpy(t_bint src, t_bint dst)
{
	uint32_t	i;

	if ((src[0] & NBR_LENGTH) > ((dst[0] & ARR_SIZE) >> 16) - 1)
		return (0);
	i = 0;
	while (i < (src[0] & NBR_LENGTH))
	{
		++i;
		dst[i] = src[i];
	}
	dst[0] = (dst[0] & ~NBR_LENGTH) + i;
	return (1);
}

int		bintset(uint64_t u, t_bint dst)
{
	uint32_t	i;

	i = 0;
	while (u)
	{
		if (i == ((dst[0] & ARR_SIZE) >> 16) - 1)
			return (0);
		dst[++i] = (uint32_t)(u & 0xFFFFFFFF);
		u >>= 32;
	}
	dst[0] = (dst[0] & ~NBR_LENGTH) + i;
	return (1);
}

int		bintcmp(t_bint l, t_bint r)
{
	int	i;

	if ((l[0] & NBR_LENGTH) != (r[0] & NBR_LENGTH))
		return ((l[0] & NBR_LENGTH) - (r[0] & NBR_LENGTH));
	i = l[0] & NBR_LENGTH;
	while (i > 0 && l[i] == r[i])
		--i;
	if (i == 0)
		return (0);
	else
		return (l[i] > r[i] ? 1 : -1);
}

void	bintclr(t_bint b)
{
	while (b[0] & NBR_LENGTH)
		b[b[0]-- & NBR_LENGTH] = 0;
}

void	bintinit(t_bint b, uint32_t size)
{
	size = size ? size : BINT_SIZE;
	b[0] = (size << 16) + size - 1;
	bintclr(b);
}
