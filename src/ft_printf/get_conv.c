/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 18:34:46 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/25 10:10:42 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

static int	get_type(char **fmt, t_params *conv)
{
	char	*t;

	//TODO: replace this string by the ft_printf_internal macro
	//TODO: also add '%' to the g_conversions array and see how it works
	//(I'm not clear on it right now)
	t = ft_strchr("dDibBoOuUxXeEfFgGcCsSpPt%", **fmt);
	if (t && !*t)
		return (!t);
	conv->type = *(*fmt)++;
	//TODO: just DOUi map DOUi conversions to their dedicated function
	//in the g_conversions array instead of changin the type (will have
	//to think about formatting and more loargely everywhere we use
	//conv->type so that these conversions are included in where they
	//need to be)
	if (conv->type == 'D' || conv->type == 'O' || conv->type == 'U')
	{
		conv->cast = conv->type == 'D' ? C_LONG : C_LONG | C_UNSIGNED;
		conv->type += 32;
	}
	else if (ft_strchr("bBouxX", conv->type))
		conv->cast |= C_UNSIGNED;
	else if ((conv->type == 'c' || conv->type == 's') && conv->cast & C_LONG)
		conv->type -= 32;
	else if (conv->type == 'i')
		conv->type = 'd';
	return (1);
}

static int	get_cast(char **fmt, t_params *conv)
{
	int	ret;

	ret = 0;
	while (ft_strchr("hljzL", **fmt) && **fmt)
	{
		if (**fmt == 'h' && !(conv->cast & C_SHORT))
			conv->cast |= C_SHORT;
		else if (**fmt == 'h')
			conv->cast = (conv->cast | C_CHAR) & ~C_SHORT;
		else if (**fmt == 'l' && !(conv->cast & C_LONG))
			conv->cast |= C_LONG;
		else if (**fmt == 'l' || **fmt == 'L')
			conv->cast = (conv->cast | C_LONG_LONG) & ~C_LONG;
		else if (**fmt == 'j')
			conv->cast |= C_INTMAX_T;
		else if (**fmt == 'z')
			conv->cast |= C_SIZE_T;
		(*fmt)++;
		ret = 1;
	}
	return (ret);
}

int			get_conv(char **fmt, t_farg *args, t_params *conv)
{
	int		f;
	int		c;

	(*fmt)++;
	f = 1;
	c = 1;
	while (f || c)
	{
		if ((f = get_flags(fmt, args, conv)) < 0)
			return (0);
		c = get_cast(fmt, conv);
	}
	return (get_type(fmt, conv));
}
