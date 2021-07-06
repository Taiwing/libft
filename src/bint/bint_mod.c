/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:18:25 by yforeau           #+#    #+#             */
/*   Updated: 2021/07/06 14:11:11 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "bint.h"

static int	bint_smod(t_bint res, const t_bint mod)
{
	uint32_t	tmp[BINT_SIZE_DEF];

	bintinit(tmp, 0);
	if (bintcpy(tmp, res))
		return (BINT_FAILURE);
	return (bint_divide(NULL, res, tmp, mod));
}

static int	bint_smult(t_bint res, const t_bint r)
{
	uint32_t	tmp[BINT_SIZE_DEF];

	bintinit(tmp, 0);
	if (bint_mult(tmp, res, r) == BINT_FAILURE
		|| bintcpy(res, tmp) == BINT_FAILURE)
		return (BINT_FAILURE);
	return (BINT_SUCCESS);
}

int			bint_modexp(t_bint res, const t_bint a,
	const t_bint b, const t_bint c)
{
	uint32_t	local_a[BINT_SIZE_DEF];
	uint32_t	local_b[BINT_SIZE_DEF];

	bintinit(local_a, 0);
	bintinit(local_b, 0);
	if (bintcpy(local_a, a) == BINT_FAILURE
		|| bintcpy(local_b, b) == BINT_FAILURE
		|| bintcpy(res, g_bint_one) == BINT_FAILURE
		|| bint_smod(local_a, c) == BINT_FAILURE)
		return (BINT_FAILURE);
	while (bintcmp(local_b, g_bint_zero))
	{
		if (bint_is_odd(local_b)
			&& (bint_smult(res, local_a) == BINT_FAILURE
			|| bint_smod(res, c) == BINT_FAILURE))
			return (BINT_FAILURE);
		if (bint_smult(local_a, local_a) == BINT_FAILURE
			|| bint_smod(local_a, c) == BINT_FAILURE
			|| bint_shiftright(local_b, 1) == BINT_FAILURE)
			return (BINT_FAILURE);
	}
	return (BINT_SUCCESS);
}
