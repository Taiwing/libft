/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secmalloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 12:44:15 by yforeau           #+#    #+#             */
/*   Updated: 2019/02/06 12:53:20 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SECMALLOC_H
# define FT_SECMALLOC_H

# include "libft.h"

/*
** The macro EXIT_ON_MALLOC_FAIL will be either defined or not in libft.h,
** if it is, then every malloc used in libft will be replaced ft_secmalloc
** else, regular malloc will be used
*/
# ifdef EXIT_ON_MALLOC_FAIL
#  define malloc ft_secmalloc
# endif

#endif
