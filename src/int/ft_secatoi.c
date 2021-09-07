/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secatoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 23:50:36 by yforeau           #+#    #+#             */
/*   Updated: 2021/09/08 00:00:13 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_secatoi: like atoi but with an overflow, underflow and input check
*/
int	ft_secatoi(int *dest, int min, int max, const char *nptr)
{
	long long int	nb;
	long long int	sign;

	if (!*nptr)
		return (FT_E_NOT_A_NUMBER);
	nb = 0;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
		sign = *nptr++ == '-' ? -1 : sign;
	while (*nptr > 47 && *nptr < 58 && nb <= max)
		nb = (nb * 10) + ((*nptr++) - 48);
	if (*nptr && (*nptr <= 47 || *nptr >= 58))
		return (FT_E_NOT_A_NUMBER);
	else if (nb * sign > max)
		return (FT_E_OVERFLOW);
	else if (nb * sign < min)
		return (FT_E_UNDERFLOW);
	*dest = nb * sign;
	return (0);
}
