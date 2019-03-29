/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wtfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:04:19 by yforeau           #+#    #+#             */
/*   Updated: 2019/03/29 20:11:56 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#ifdef NO_COLLEC

void	ft_wtfree(char **wt)
{
	char	**ptr;

	if (!wt)
		return ;
	ptr = wt;
	while (*wt)
		free(*wt++);
	free(*wt);
	free(ptr);
}

#else

# include "ft_collector.h"

void	ft_wtfree(char **wt)
{
	char	**ptr;

	if (!wt)
		return ;
	ptr = wt;
	while (*wt)
		free(ft_heap_collector(*wt++, FT_COLLEC_GET));
	free(ft_heap_collector(*wt, FT_COLLEC_GET));
	free(ft_heap_collector(ptr, FT_COLLEC_GET));
}

#endif
