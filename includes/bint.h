/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:01:14 by yforeau           #+#    #+#             */
/*   Updated: 2021/04/14 19:20:13 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINT_H
# define BINT_H

# include <stdint.h>
# define BINT_SIZE 		520
# define SIZE_UINTMAX	2
# define NBR_LENGTH		0x0000FFFF
# define ARR_SIZE		0xFFFF0000

/*
** size 36 makes it possible to represent up to 1120 bits unsigned integers
** size 520 makes it possible to represent up to 16608 bits unsigned integers
** NBR_LENGTH is the number of blocks occupied by the number (0 means value 0)
** ARR_SIZE total size of the array (so total number of blocks + 1)
*/

typedef uint32_t *	t_bint;

/*
** bint utility functions
*/

int					bintcpy(t_bint src, t_bint dst);
int					bintset(uint64_t u, t_bint dst);
int					bintcmp(t_bint l, t_bint r);
void				bintclr(t_bint b);
void				bintinit(t_bint b, uint32_t size);

/*
** bint operations
*/

int					add_bint(t_bint res, t_bint l, t_bint r);
int					sadd_32bint(t_bint res, uint32_t rig);

int					mult_bint(t_bint res, t_bint l, t_bint r);
int					mult_32bint(t_bint res, t_bint lef, uint32_t rig);
int					mult2_bint(t_bint res, t_bint in);
int					smult2_bint(t_bint res);
int					smult10_bint(t_bint res);

int					pow10_bint(t_bint res, uint32_t exp);
int					multpow10_bint(t_bint res, t_bint in, uint32_t exp);
int					pow2_bint(t_bint res, uint32_t exp);

uint32_t			divmod_max9_bint(t_bint dividend, t_bint divisor);
int					shiftleft_bint(t_bint res, uint32_t shift);

#endif
