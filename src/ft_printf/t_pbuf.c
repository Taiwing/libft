/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pbuf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:44:45 by yforeau           #+#    #+#             */
/*   Updated: 2019/02/14 16:14:16 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_pbuf.h"
#include "libft.h"

void	init_pbuf(t_pbuf *buf, int fd)
{
	buf->fd = fd;
	buf->n = 0;
}

void	add_to_pbuf(t_pbuf *buf, char *add, int c, size_t size)
{
	if (buf->n + size > PBUF_SIZE)
		flush_pbuf(buf);
	while (size > PBUF_SIZE && buf->n != -1)
	{
		if (add)
		{
			write(buf->fd, add, PBUF_SIZE);
			add += PBUF_SIZE;
		}
		else
		{
			ft_memset((void *)buf->b, c, PBUF_SIZE);
			write(buf->fd, buf->b, PBUF_SIZE);
		}
		size -= PBUF_SIZE;
	}
	if (buf->n != -1 && size > 0)
	{
		if (add)
			ft_memcpy((void *)(buf->b + buf->n), (void *)add, size);
		else
			ft_memset((void *)(buf->b + buf->n), c, size);
		buf->n += size;
	}
}

void	flush_pbuf(t_pbuf *buf)
{
	if (buf->n == -1)
		return ;
	buf->n = write(buf->fd, buf->b, buf->n);
	if (buf->n > 0)
		buf->n = 0;
}
