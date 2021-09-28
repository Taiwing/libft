/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:57:52 by yforeau           #+#    #+#             */
/*   Updated: 2021/09/28 09:04:47 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef THREAD_SAFE

void			ft_mutex_lock(pthread_mutex_t *mutex)
{
	int		ret;

	if (!(ret = pthread_mutex_lock(mutex)))
		return;
	ft_exit("pthread_mutex_lock", ret, EXIT_FAILURE);
}

void			ft_mutex_unlock(pthread_mutex_t *mutex)
{
	int		ret;

	if (!(ret = pthread_mutex_unlock(mutex)))
		return;
	ft_exit("pthread_mutex_unlock", ret, EXIT_FAILURE);
}

#endif
