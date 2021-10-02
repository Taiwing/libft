/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_atexit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:03:43 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/02 17:34:17 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef THREAD_SAFE

#define THREAD_ATEXIT_MAX	1024

/*
** ft_thread_exit: simple ft_thread_atexit compatible exit call
*/
void	ft_thread_exit(void)
{
	pthread_exit(NULL);
}

/*
** ft_thread_atexit: thread local atexit handlers
**
** These handlers are called before ft_atexit in ft_exit if any are set.
*/
void	ft_thread_atexit(t_atexitf handler)
{
	static __thread t_atexitf	farr[THREAD_ATEXIT_MAX];
	static __thread size_t		i = 0;

	if (!handler)
	{
		while (i > 0)
			farr[--i]();
	}
	else if (i < THREAD_ATEXIT_MAX)
		farr[i++] = handler;
	else
	{
		handler();
		ft_exit("ft_thread_atexit: no space left", 0, EXIT_FAILURE);
	}
}

#endif
