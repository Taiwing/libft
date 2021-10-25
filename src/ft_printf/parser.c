/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:34:35 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/25 09:35:10 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf_internal.h"
#include "libft.h"

//TODO: Create an array of functions for convert instead of using 'if else ifs'
//statements. It will be waaaaay cleaner, and faster too.

const t_convf	g_conversions[CHAR_MAX + 1] = {
	['d'] = itoa_cast,
	['b'] = itoa_cast,
	['B'] = itoa_cast,
	['o'] = itoa_cast,
	['u'] = itoa_cast,
	['x'] = itoa_cast,
	['X'] = itoa_cast,
	['e'] = efg_conversions,
	['E'] = efg_conversions,
	['f'] = efg_conversions,
	['F'] = efg_conversions,
	['g'] = efg_conversions,
	['G'] = efg_conversions,
	['p'] = p_conversion,
	['P'] = p_conversion,
	['c'] = c_conversion,
	['C'] = lc_conversion,
	['s'] = s_conversion,
	['S'] = ls_conversion,
	['t'] = t_conversion,
};

static void	convert(t_pdata *data, t_farg *args, t_params *conv, char **fmt)
{
	t_pdata	loc_data;
	t_convf	convf;
	uint8_t	type;

	pdata_init(&loc_data, data->flags, data->fd);
	pdata_local_set_buf(&loc_data);
	type = conv->type < 0 ? 0 : (uint8_t)conv->type;
	if ((convf = g_conversions[type]))
		convf(&loc_data, args, conv, fmt);
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
