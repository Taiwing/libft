/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon42.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:57:21 by yforeau           #+#    #+#             */
/*   Updated: 2021/05/04 07:48:16 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dragon4.h"
#include "bint.h"
#include "log_and_ceil.h"
#include "ft_printf.h"

static int	scale_val(t_bint scale, t_bint scaled_val, const t_bint n)
{
	int			ret;
	uint32_t	log2;
	int			digit_exp;
	uint32_t	tmp[BINT_SIZE_DEF];

	bintinit(tmp, 0);
	bintset_u64(scale, 2);
	log2 = logbase2_32(n[BINT_LEN(n)]) + ((BINT_LEN(n) - 1) * 32);
	digit_exp = ft_ceil(((int)log2) * LOG10_2 - 0.69);
	ret = BINT_SUCCESS;
	if (digit_exp > 0)
	{
		ret = bint_multpow10(tmp, scale, digit_exp);
		ret = ret == BINT_SUCCESS ? bintcpy(scale, tmp) : ret;
	}
	if (ret == BINT_SUCCESS && bintcmp(scaled_val, scale) < 0)
		ret = bint_smult10(scaled_val);
	return (ret);
}

#define DIGIT_BUFLEN 128

int		bint_print(const t_bint n, uint32_t info, uint32_t base); //TEMP

//TODO: Rethink about how the loop stops, the problem is when it stops
// at 0, if the value a multiple of 10, it will not add the needed '0'
// at the end of the number. The log10 needs to be kept because this is
// really how the algorithm stops. The stop at !BINT_LEN(res) is an
// optimization of dragon4. This is because from this point we know there
// are no more significant digits, so the buffer can be filled to the end
// with 0's
static int	binttostr(t_bint scale, t_bint scaled_val, char *cur_digit, int fd)
{
	int			err;
	int			count;
	int			digit;
	char		*buf;
	char		static_buf[DIGIT_BUFLEN];

	err = 0;
	count = 0;
	buf = !cur_digit ? static_buf : cur_digit;
	//TEMP
	ft_printf("scaled_val:\n");
	bint_print(scaled_val, 1, 16);
	ft_printf("scale:\n");
	bint_print(scale, 1, 16);
	//TEMP
	while (BINT_LEN(scaled_val) && !err)
	{
		digit = bint_divmod_max9(scaled_val, scale);
		*buf++ = (char)(48 + digit);
		++count;
		err = digit == 10;
		//TEMP
		ft_printf("digit = %d\n", digit);
		ft_printf("scaled_val after divmod_max9:\n");
		bint_print(scaled_val, 1, 16);
		//TEMP
		if (!cur_digit && !(count % DIGIT_BUFLEN) && !err)
		{
			ft_dprintf(fd, "%.*s", DIGIT_BUFLEN, static_buf);
			buf = static_buf;
		}
		err = !err ? bint_smult10(scaled_val) == BINT_FAILURE : err;
		//TEMP
		ft_printf("scaled_val after smult10:\n");
		bint_print(scaled_val, 1, 16);
		return (-1);
		//TEMP
	}
	if (!err && (count % DIGIT_BUFLEN))
		ft_dprintf(fd, "%.*s", DIGIT_BUFLEN, buf);
	return (!err ? count : -1);
}

int			dragon42(char *buf, int fd, const t_bint n)
{
	uint32_t	scaled_val[BINT_SIZE_DEF];
	uint32_t	scale[BINT_SIZE_DEF];
	uint32_t	prec;
	int			err;

	if (!BINT_LEN(n))
	{
		if (buf)
			*buf = '0';
		else
			ft_dprintf(fd, "0");
		return (1);
	}
	bintinit(scale, 0);
	bintinit(scaled_val, 0);
	err = bint_mult2(scaled_val, n) == BINT_FAILURE;
	err = !err ? scale_val(scale, scaled_val, n) == BINT_FAILURE : err;
	if (!err && (scale[BINT_LEN(scale)] < 8
		|| scale[BINT_LEN(scale)] > 429496729))
	{
		prec = (32 + 27 - logbase2_32(scale[BINT_LEN(scale)])) % 32;
		err = !err ? bint_shiftleft(scale, prec) == BINT_FAILURE : err;
		err = !err ? bint_shiftleft(scaled_val, prec) == BINT_FAILURE : err;
	}
	return (err ? -1 : binttostr(scale, scaled_val, buf, fd));
}
