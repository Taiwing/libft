/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bufprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:21:57 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/22 19:02:36 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_pbuf.h"
#include "parser.h"
#include "libft.h"

int	ft_bufprintf(t_pbuf *buf, const char *format, ...)
{
	t_farg	args = { 0 };

	va_start(args.cur, format);
	va_copy(args.ref, args.cur);
	while (*format && buf->n != -1)
		parser_pbuf(buf, (char **)&format, &args);
	va_end(args.cur);
	va_end(args.ref);
	return (buf->n);
}
