/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 05:43:30 by yforeau           #+#    #+#             */
/*   Updated: 2022/02/26 07:31:24 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_result(t_scanres *result, t_scan scan)
{
	ft_printf("\nResult (%d):\n", scan);
	ft_printf("rtt: tv_sec = %lld, tv_usec = %lld\n",
		result->rtt.tv_sec, result->rtt.tv_usec);
	ft_printf("ttl: %hhu\n", result->ttl);
	ft_printf("open: %s\n", result->open ? "true" : "false");
	ft_printf("reason: %d\n", result->reason);
	ft_printf("sequence: %hu\n", result->sequence);

	// DEBUG
	t_scan_control	*scan_ctrl;
	if (!(scan_ctrl = ft_get_scan(scan)))
		ft_exit(EXIT_FAILURE, "ft_get_scan: %s", ft_strerror(ft_errno));
	ft_printf("sequence from scan_control: %hu\n", scan_ctrl->sequence);
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

static void	send_probes(t_pollsc *scans, int host_count)
{
	for (int i = 0; i < host_count; ++i)
		if (ft_scan_send(scans[i].scan) < 0)
			ft_exit(EXIT_FAILURE, "ft_scan_send: %s", ft_strerror(ft_errno));
}

static int	get_results(int *done, t_pollsc *scans, int host_count)
{
	int			count = 0;
	t_scanres	result = { 0 };

	for (int i = 0; i < host_count; ++i)
	{
		if (scans[i].events || done[i])
			++count;
		if (!scans[i].events || done[i])
			continue;
		ft_printf("\n");
		print_events(scans[i].events);
		if (ft_scan_result(&result, scans[i].scan) < 0)
			ft_exit(EXIT_FAILURE, "ft_scan_result: %s", ft_strerror(ft_errno));
		print_result(&result, scans[i].scan);
		done[i] = 1;
	}
	return (count == host_count);
}

#define	MAX_ARGS	256

int	main(int argc, char **argv)
{
	int				ret;
	int				done[MAX_ARGS] = { 0 };
	t_ip			ip[MAX_ARGS] = { 0 };
	int				host_count = argc - 1;
	t_pollsc		scans[MAX_ARGS] = { 0 };
	struct timeval	timeout = { 5, 0 };
	char			buf[INET6_ADDRSTRLEN];

	if (host_count > MAX_ARGS)
		ft_exit(EXIT_FAILURE, "no more than %d hosts\n", MAX_ARGS);
	if (!host_count)
		ft_exit(EXIT_FAILURE, "Usage: %s host...", argv[0]);
	ft_atexit(ft_scan_close_all);
	for (int i = 0; i < host_count; ++i)
	{
		if ((ret = ft_get_ip(ip + i, argv[i + 1], AF_UNSPEC)) < 0)
			ft_exit(EXIT_FAILURE, "ft_get_ip: %s", gai_strerror(ret));
		ft_printf("IP: %s\n", inet_ntop(ip[i].family, ft_ip_addr(ip + i),
			buf, INET6_ADDRSTRLEN));
		if ((scans[i].scan = ft_echo_ping_open(ip + i, &timeout)) < 0)
			ft_exit(EXIT_FAILURE, "ft_echo_ping_open: %s",
				ft_strerror(ft_errno));
	}
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
	send_probes(scans, host_count);
	while ((ret = ft_scan_poll(scans, host_count, NULL)) >= 0)
	{
		if (!ret) continue;
		if (get_results(done, scans, host_count))
		{
			ft_bzero(done, sizeof(done));
			sleep(1);
			send_probes(scans, host_count);
		}
	}
	ft_exit(EXIT_FAILURE, "ft_scan_poll: %s", ft_strerror(ft_errno));
	return (EXIT_SUCCESS);
}
