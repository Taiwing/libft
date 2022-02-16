/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:21:33 by yforeau           #+#    #+#             */
/*   Updated: 2022/02/16 15:43:50 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_errno global declaration
*/
#ifdef THREAD_SAFE
__thread int	ft_errno = 0;
#else
int				ft_errno = 0;
#endif

/*
** Every libft error string. Update this when adding an error to e_libft_errors
** in ft_errno.h to make sure every error code corresponds to a valid string.
*/
const char	*g_errors[E_FTERR_MAX] = {
	// Invalid error format string
	"Unknown error %d",

	// Network errors
	"invalid protocol",
	"invalid IP family",
	"missing IP address",
	"invalid port range",
	"setsockopt failure",
	"invalid header level",
	"sendto failure",
	"socket failure",
};

#define SIZE_INVALID_FTERR	32

/*
** ft_strerror: turn an error code (possibly from ft_errno) into an error string
**
** The resulting string is not to be modified by the user. Also it might be
** reset if the user calls ft_strerror again (only in the case where the error
** code is not known). If the error code is not a valid libft error it will
** return a formatted string with the erroneous error code inside.
**
** This function is thread-safe.
*/
char		*ft_strerror(int error)
{
#ifdef THREAD_SAFE
	static __thread char	invalid_error_buf[SIZE_INVALID_FTERR] = { 0 };
#else
	static char				invalid_error_buf[SIZE_INVALID_FTERR] = { 0 };
#endif
	
	if (error > E_FTERR_MIN && error < E_FTERR_MAX)
		return ((char *)g_errors[error]);
	ft_snprintf(invalid_error_buf, SIZE_INVALID_FTERR,
		g_errors[E_FTERR_MIN], error);
	return (invalid_error_buf);
}
