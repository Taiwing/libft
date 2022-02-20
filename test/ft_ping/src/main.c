/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 05:43:30 by yforeau           #+#    #+#             */
/*   Updated: 2022/02/20 07:02:51 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(int argc, char **argv)
{
	t_ip			ip;
	int				ret;
	t_scan			scan;
	t_scanres		result = { 0 };
	char			*host = argv[1];
	struct timeval	timeout = { 5, 0 };
	char			buf[INET6_ADDRSTRLEN];

	(void)argc;
	if (!host)
		ft_exit(EXIT_FAILURE, "Usage: %s host...", argv[0]);
	if ((ret = ft_get_ip(&ip, host, AF_UNSPEC)) < 0)
		ft_exit(EXIT_FAILURE, "ft_get_ip: %s", gai_strerror(ret));
	ft_printf("IP: %s\n", inet_ntop(ip.family, ft_ip_addr(&ip),
		buf, INET6_ADDRSTRLEN));
	ft_atexit(ft_scan_close_all);
	if ((scan = ft_echo_ping_open(&ip, &timeout)) < 0)
		ft_exit(EXIT_FAILURE, "ft_echo_ping_open: %s", ft_strerror(ft_errno));
	if (ft_echo_ping(&result, scan) < 0)
		ft_exit(EXIT_FAILURE, "ft_echo_ping: %s", ft_strerror(ft_errno));
	ft_scan_close(scan);
	return (EXIT_SUCCESS);
}
