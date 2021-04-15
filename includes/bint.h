/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:01:14 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/15 11:09:16 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINT_H
# define BINT_H

# include <stdint.h>
# define BINT_SIZE_DEF			520
# define SIZE_UINTMAX			2
# define BINT_LEN_MASK			0x0000FFFF
# define BINT_SIZE_MASK			0xFFFF0000
# define BINT_LEN(n)			(n[0] & BINT_LEN_MASK)
# define BINT_SIZE(n)			((n[0] & BINT_SIZE_MASK) >> 16)
# define SET_BINT_LEN(n, len)	(n[0] = (n[0] & ~BINT_LEN_MASK) + len)

/*
** size 36 makes it possible to represent up to 1120 bits unsigned integers
** size 520 makes it possible to represent up to 16608 bits unsigned integers
** BINT_LEN is the number of blocks occupied by the number (0 means value 0)
** BINT_SIZE total size of the array (so total number of blocks + 1)
*/

typedef uint32_t *	t_bint;

/*
** bint utility functions
*/

int					bintcpy(t_bint dst, t_bint src);
int					bintset(uint64_t u, t_bint dst);
int					bintcmp(t_bint l, t_bint r);
void				bintclr(t_bint b);
void				bintinit(t_bint b, uint32_t size);

/*
** bint operations
*/

int					bint_add(t_bint res, t_bint l, t_bint r);
int					bint_sadd_u32(t_bint res, uint32_t rig);

int					bint_mult(t_bint res, t_bint l, t_bint r);
int					bint_mult_u32(t_bint res, t_bint lef, uint32_t rig);
int					bint_mult2(t_bint res, t_bint in);
int					bint_smult2(t_bint res);
int					bint_smult10(t_bint res);

int					bint_pow10(t_bint res, uint32_t exp);
int					bint_multpow10(t_bint res, t_bint in, uint32_t exp);
int					bint_pow2(t_bint res, uint32_t exp);

uint32_t			bint_divmod_max9(t_bint dividend, t_bint divisor);
int					bint_shiftleft(t_bint res, uint32_t shift);

#endif
