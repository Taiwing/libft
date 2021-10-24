/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:43:15 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/24 13:24:30 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

int	ft_printf(const char *format, ...)
{
	t_farg	args = { 0 };
	t_pdata	data;

	pdata_init(&data, PMODE_CLASSIC, 1);
	pdata_set_buf(&data, NULL, 0);
	va_start(args.cur, format);
	va_copy(args.ref, args.cur);
	while (*format && data.n != -1)
		parser(&data, (char **)&format, &args);
	pdata_print(&data);
	va_end(args.cur);
	va_end(args.ref);
	return (data.n);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_farg	args = { 0 };
	t_pdata	data;

	pdata_init(&data, PMODE_CLASSIC, fd);
	pdata_set_buf(&data, NULL, 0);
	va_start(args.cur, format);
	va_copy(args.ref, args.cur);
	while (*format && data.n != -1)
		parser(&data, (char **)&format, &args);
	pdata_print(&data);
	va_end(args.cur);
	va_end(args.ref);
	return (data.n);
}

int	ft_sprintf(char *str, const char *format, ...)
{
	t_farg	args = { 0 };
	t_pdata	data;

	pdata_init(&data, PMODE_NOLIMIT, -1);
	pdata_set_buf(&data, str, 0);
	va_start(args.cur, format);
	va_copy(args.ref, args.cur);
	while (*format && data.n != -1)
		parser(&data, (char **)&format, &args);
	if (data.n != -1)
		str[data.n] = 0;
	va_end(args.cur);
	va_end(args.ref);
	return (data.n);
}

int	ft_snprintf(char *str, int size, const char *format, ...)
{
	t_farg	args = { 0 };
	t_pdata	data;

	if (!size)
		return (0);
	pdata_init(&data, PMODE_BUFLIMIT, -1);
	pdata_set_buf(&data, str, (size_t)size);
	va_start(args.cur, format);
	va_copy(args.ref, args.cur);
	while (*format && data.n != -1 && data.n < size - 1)
		parser(&data, (char **)&format, &args);
	if (data.n != -1)
		str[data.n] = 0;
	va_end(args.cur);
	va_end(args.ref);
	return (data.n);
}

int	ft_asprintf(char **str, const char *format, ...)
{
	t_farg	args = { 0 };
	t_pdata	data;

	pdata_init(&data, PMODE_BUFALLOC, -1);
	pdata_set_buf(&data, NULL, 0);
	va_start(args.cur, format);
	va_copy(args.ref, args.cur);
	while (*format && data.n != -1)
		parser(&data, (char **)&format, &args);
	if (data.n != -1)
	{
		*str = data.buf;
		(*str)[data.n] = 0;
	}
	else
		ft_memdel((void **)&data.buf);
	va_end(args.cur);
	va_end(args.ref);
	return (data.n);
}
