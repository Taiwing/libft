/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wtdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:11:08 by yforeau           #+#    #+#             */
/*   Updated: 2021/09/22 23:53:57 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef NO_COLLEC

#ifdef THREAD_SAFE
MUTEXIFY(char**, ft_wtdup, char**, wt)
#else
char	**ft_wtdup(char **wt)
#endif
{
	static int	size = 0;
	char		*p;
	char		**tb;

	if (!wt)
		return (NULL);
	tb = NULL;
	size = size == -1 ? 1 : size + 1;
	if (*wt && !(p = ft_strdup(*wt)))
		size = -1;
	else if (!*wt)
		p = NULL;
	if (size != -1 && !(tb = p ? ft_wtdup(++wt) :
		(char **)ft_secmalloc(size * sizeof(char *))))
		size = -1;
	if (size == -1 && p)
		free(p);
	else if (size != -1)
		tb[--size] = p;
	return (tb);
}

#else

#ifdef THREAD_SAFE
MUTEXIFY(char**, ft_wtdup, char**, wt)
#else
char	**ft_wtdup(char **wt)
#endif
{
	static int	size = 0;
	char		*p;
	char		**tb;

	if (!wt)
		return (NULL);
	tb = NULL;
	size = size == -1 ? 1 : size + 1;
	if (*wt && !(p = ft_strdup(*wt)))
		size = -1;
	else if (!*wt)
		p = NULL;
	if (size != -1 && !(tb = p ? ft_wtdup(++wt) :
		(char **)ft_secmalloc(size * sizeof(char *))))
		size = -1;
	if (size == -1 && p)
		free(ft_heap_collector(p, FT_COLLEC_GET));
	else if (size != -1)
		tb[--size] = p;
	return (tb);
}

#endif
