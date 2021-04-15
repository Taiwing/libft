/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:01:14 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/15 12:40:45 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINT_H
# define BINT_H

# include <stdint.h>

/*
** size 36 makes it possible to represent up to 1120 bits unsigned integers
** size 520 makes it possible to represent up to 16608 bits unsigned integers
** BINT_LEN is the number of blocks occupied by the number (0 means value 0)
** BINT_SIZE total size of the array (so total number of blocks + 1)
**
** Every bint function will return BINT_FAILURE on failure and BINT_SUCCESS
** otherwise. The two exceptions are bintcmp which has a strcmp type return
** and bint_divmod_max9 which returns a quotient (returns 10 on error).
*/

# define BINT_SIZE_DEF			520
# define SIZE_UINTMAX			2
# define BINT_LEN_MASK			0x0000FFFF
# define BINT_SIZE_MASK			0xFFFF0000
# define BINT_LEN(n)			(n[0] & BINT_LEN_MASK)
# define BINT_SIZE(n)			((n[0] & BINT_SIZE_MASK) >> 16)
# define SET_BINT_LEN(n, len)	(n[0] = (n[0] & ~BINT_LEN_MASK) + len)
# define BINT_FAILURE			1
# define BINT_SUCCESS			0

typedef uint32_t *	t_bint;

/*
** bint utility functions
*/

int					bintcpy(t_bint dst, const t_bint src);
int					bintset(t_bint dst, uint64_t u);
int					bintcmp(const t_bint l, const t_bint r);
void				bintclr(t_bint b);
void				bintinit(t_bint b, uint32_t size);

/*
** bint operations
*/

int					bint_add(t_bint res, const t_bint l, const t_bint r);
int					bint_sadd_u32(t_bint res, uint32_t rig);

int					bint_mult(t_bint res, const t_bint l, const t_bint r);
int					bint_mult_u32(t_bint res, const t_bint lef, uint32_t rig);
int					bint_mult2(t_bint res, const t_bint in);
int					bint_smult2(t_bint res);
int					bint_smult10(t_bint res);

int					bint_pow10(t_bint res, uint32_t exp);
int					bint_multpow10(t_bint res, const t_bint in, uint32_t exp);
int					bint_pow2(t_bint res, uint32_t exp);

uint32_t			bint_divmod_max9(t_bint dividend, const t_bint divisor);
int					bint_shiftleft(t_bint res, uint32_t shift);

#endif
