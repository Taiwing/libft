/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 14:22:04 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/02 14:22:12 by yforeau          ###   ########.fr       */
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
