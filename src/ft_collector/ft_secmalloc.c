/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 08:10:46 by yforeau           #+#    #+#             */
/*   Updated: 2019/03/28 13:15:40 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#ifdef NO_COLLEC
# include <string.h>

void	*ft_secmalloc(size_t size)
{
	return (malloc(size));
}

# else
# include "ft_collector.h"

void	*ft_secmalloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		ft_exit("malloc failure", EXIT_FAILURE);
	ft_heap_collector(ptr, FT_COLLEC_ADD);
	return (ptr);
}

#endif
