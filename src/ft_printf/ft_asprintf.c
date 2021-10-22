/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:15:53 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/22 19:08:02 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

#ifdef NO_COLLEC

int	ft_asprintf(char **str, const char *format, ...)
{
	t_farg	args = { 0 };
	t_pdata	data;

	init_buf_alloc(&data, str);
	va_start(args.cur, format);
	va_copy(args.ref, args.cur);
	while (*format && data.n != -1)
		parser_alloc(&data, (char **)&format, &args);
	if (data.n != -1)
	{
		*str = data.buf;
		(*str)[data.n] = 0;
	}
	else
		free(data.buf);
	va_end(args.cur);
	va_end(args.ref);
	return (data.n);
}

#else

int	ft_asprintf(char **str, const char *format, ...)
{
	t_farg	args = { 0 };
	t_pdata	data;

	init_buf_alloc(&data, str);
	va_start(args.cur, format);
	va_copy(args.ref, args.cur);
	while (*format && data.n != -1)
		parser_alloc(&data, (char **)&format, &args);
	if (data.n != -1)
	{
		*str = data.buf;
		(*str)[data.n] = 0;
	}
	else
		free(ft_heap_collector(data.buf, FT_COLLEC_GET));
	va_end(args.cur);
	va_end(args.ref);
	return (data.n);
}

#endif
