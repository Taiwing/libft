/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:34:35 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/24 13:23:14 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

//TODO: Create an array of functions for convert instead of using 'if else ifs'
//statements. It will be waaaaay cleaner, and faster too.

static void	convert(t_pdata *data, t_farg *args, t_params *conv, char **fmt)
{
	t_pdata	loc_data;

	pdata_init(&loc_data, data->flags, data->fd);
	pdata_local_set_buf(&loc_data);
	if (ft_strchr("dbBouxX", conv->type))
		itoa_cast(&loc_data, args, conv);
	else if (ft_strchr("eEfFgG", conv->type))
		efg_conversions(&loc_data, args, conv);
	else if (conv->type == 'p' || conv->type == 'P')
		p_conversion(&loc_data, args, conv);
	else if (conv->type == 'c')
		c_conversion(&loc_data, args, conv);
	else if (conv->type == 'C')
		lc_conversion(&loc_data, args, conv);
	else if (conv->type == 's')
		s_conversion(&loc_data, args, conv);
	else if (conv->type == 'S')
		ls_conversion(&loc_data, args, conv);
	else if (conv->type == 't')
		t_conversion(&loc_data, args, conv, fmt);
	else
		pdata_add(&loc_data, NULL, conv->type, 1);
	if (loc_data.n != -1)
		format_data(data, &loc_data, conv);
	data->n = loc_data.n == -1 ? -1 : data->n;
	ft_memdel((void **)&loc_data.abuf);
}

void		parser(t_pdata *data, char **fmt, t_farg *args)
{
	t_params	conv = CONV_INIT;
	char		*mod;

	mod = ft_strchr(*fmt, '%');
	if (mod == *fmt)
	{
		if (get_conv(fmt, args, &conv))
			convert(data, args, &conv, fmt);
	}
	else if (mod)
	{
		pdata_add(data, *fmt, 0, mod - *fmt);
		*fmt = mod;
	}
	else
	{
		pdata_add(data, *fmt, 0, ft_strlen(*fmt));
		*fmt = ft_strchr(*fmt, 0);
	}
}
