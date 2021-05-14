/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_bint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:16:39 by yforeau           #+#    #+#             */
/*   Updated: 2021/05/14 15:34:38 by yforeau          ###   ########.fr       */
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

void	bintclean(t_bint b)
{
	uint32_t	len;

	for (uint32_t i = BINT_SIZE(b) - 1; i > BINT_LEN(b); --i)
		b[i] = 0;
	for (len = BINT_LEN(b); len > 0 && !b[len]; --len);
	SET_BINT_LEN(b, len);
}

void	bintclr(t_bint b)
{
	SET_BINT_LEN(b, 0);
	bintclean(b);
	SET_BINT_SIGN(b, 0);
}

void	bintinit(t_bint b, uint32_t size)
{
	size = size ? size : BINT_SIZE_DEF;
	b[0] = size << 16;
	bintclr(b);
}
