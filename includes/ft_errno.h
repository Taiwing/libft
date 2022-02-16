/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:05:41 by yforeau           #+#    #+#             */
/*   Updated: 2022/02/16 15:42:58 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERRNO_H
# define FT_ERRNO_H

/*
** ft_errno works like the original errno. It is set to 0 at start and can be
** set to any valid error value by some libft functions. It also can be thread
** safe if needed.
*/

#  ifdef THREAD_SAFE
	extern __thread int	ft_errno;
#  else
	extern int			ft_errno;
#  endif

/*
** ft_errno functions
*/
char	*ft_strerror(int error);

/*
** libft errors. Update this to add a possible value for ft_errno. Do not forget
** to update the g_errors structure in ft_errno.c to make sure it corresponds to
** a valid error string.
*/
enum e_libft_errors	{
	//First value to detect invalid error codes
	E_FTERR_MIN = 0,

	// Network errors
	E_FTERR_NET_INVALID_PROTOCOL,
	E_FTERR_NET_INVALID_IP_FAMILY,
	E_FTERR_PACKET_FILTER_NULL_IP,
	E_FTERR_PACKET_FILTER_INVALID_PORT_RANGE,
	E_FTERR_SETSOCKOPT,
	E_FTERR_PACKET_INVALID_HEADER_LEVEL,
	E_FTERR_SENDTO,
	E_FTERR_SOCKET,

	//Last value to detect invalid error codes
	E_FTERR_MAX,
};

#endif
