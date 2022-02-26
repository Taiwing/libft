/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 05:43:30 by yforeau           #+#    #+#             */
/*   Updated: 2022/02/26 06:34:07 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_result(t_scanres *result)
{
	ft_printf("\nResult:\n");
	ft_printf("rtt: tv_sec = %lld, tv_usec = %lld\n",
		result->rtt.tv_sec, result->rtt.tv_usec);
	ft_printf("ttl: %hhu\n", result->ttl);
	ft_printf("open: %s\n", result->open ? "true" : "false");
	ft_printf("reason: %d\n", result->reason);
	ft_printf("sequence: %hu\n", result->sequence);
	ft_printf("sequence from scan_control: %hu\n",
		g_scan_list[E_FTSCAN_ECHO_PING][0]->sequence);
}

static void	print_events(uint16_t events)
{
	uint16_t	bit;
	int			is_first = 1;

	ft_printf("event:");
	if (!events)
		ft_printf(" NONE");
	for (int i = 0; i < 16 && events; ++i)
	{
		bit = events & 1;
		events >>= 1;
		switch (bit << i)
		{
			case E_POLLSC_NONE:											break;
			case E_POLLSC_REPLY:
				ft_printf("%s REPLY", is_first ? "" : "|");				break;
			case E_POLLSC_TIMEOUT:
				ft_printf("%s TIMEOUT", is_first ? "" : "|");			break;
			case E_POLLSC_ERROR:
				ft_printf("%s ERROR", is_first ? "" : "|");				break;
			default:
				ft_printf("%s unknown event %d", is_first ? "" : "|");	break;
		}
		if (bit)
			is_first = 0;
	}
	ft_printf("\n");
}

int	main(int argc, char **argv)
{
	t_ip			ip;
	int				ret;
	t_scan			scan;
	t_pollsc		scans = { 0 };
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
	/*
	while (!(ret = ft_echo_ping(&result, scan)))
	{
		print_result(&result);
		sleep(1);
	}
	if (ret < 0)
		ft_exit(EXIT_FAILURE, "ft_echo_ping: %s", ft_strerror(ft_errno));
	ft_scan_close(scan);
	*/
	if (ft_scan_send(scan) < 0)
		ft_exit(EXIT_FAILURE, "ft_scan_send: %s", ft_strerror(ft_errno));
	scans.scan = scan;
	while ((ret = ft_scan_poll(&scans, 1, NULL)) >= 0)
	{
		if (!ret) continue;
		ft_printf("\n");
		print_events(scans.events);
		if (ft_scan_result(&result, scan) < 0)
			ft_exit(EXIT_FAILURE, "ft_scan_result: %s", ft_strerror(ft_errno));
		print_result(&result);
		sleep(1);
		if (ft_scan_send(scan) < 0)
			ft_exit(EXIT_FAILURE, "ft_scan_send: %s", ft_strerror(ft_errno));
	}
	ft_exit(EXIT_FAILURE, "ft_scan_poll: %s", ft_strerror(ft_errno));
	return (EXIT_SUCCESS);
}
