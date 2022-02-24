/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_send.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:36:07 by yforeau           #+#    #+#             */
/*   Updated: 2022/02/24 07:52:57 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define	TCP_SYN_HDR_TEMPLATE {\
	.th_sport = htons(DEF_FTSCAN_TCP_SYN_PORT),\
	.th_flags = TH_SYN,\
	.th_off = sizeof(struct tcphdr) / sizeof(uint32_t),\
	.th_win = htons(0x0ff),\
}

#define ECHO_PING_V4_HDR_TEMPLATE { .type = ICMP_ECHO }

#define ECHO_PING_V6_HDR_TEMPLATE { .icmp6_type = ICMPV6_ECHO_REQUEST }

static void	add_echo_ping_v6_header(t_packet *probe,
	t_scan_control *scan_ctrl, size_t ipsize, t_scan scan)
{
	struct icmp6hdr	hdr = ECHO_PING_V6_HDR_TEMPLATE;

	hdr.icmp6_identifier = htons(scan);
	hdr.icmp6_sequence = htons(scan_ctrl->sequence);
	ft_memcpy(probe->buf + ipsize, &hdr, sizeof(hdr));
	if (scan_ctrl->payload_size)
		ft_memcpy(probe->buf + ipsize + sizeof(hdr), scan_ctrl->payload,
			scan_ctrl->payload_size);
	/*
	// TODO: fuck. icmp6 checksum is computed from a IPv6 pseudo header. This is
	// annoying because we dont have the header at this point. It better be
	// computed by the kernel...
	((struct icmp6hdr *)(probe->buf + ipsize))->icmp6_cksum =
		ft_checksum((void *)(probe->buf + ipsize),
		sizeof(hdr) + scan_ctrl->payload_size);
	*/
}

static void	add_echo_ping_v4_header(t_packet *probe,
	t_scan_control *scan_ctrl, size_t ipsize, t_scan scan)
{
	struct icmphdr	hdr = ECHO_PING_V4_HDR_TEMPLATE;

	hdr.un.echo.id = htons(scan);
	hdr.un.echo.sequence = htons(scan_ctrl->sequence);
	ft_memcpy(probe->buf + ipsize, &hdr, sizeof(hdr));
	if (scan_ctrl->payload_size)
		ft_memcpy(probe->buf + ipsize + sizeof(hdr), scan_ctrl->payload,
			scan_ctrl->payload_size);
	((struct icmphdr *)(probe->buf + ipsize))->checksum =
		ft_checksum((void *)(probe->buf + ipsize),
		sizeof(hdr) + scan_ctrl->payload_size);
}

static void	add_tcp_syn_header(t_packet *probe, t_scan_control *scan_ctrl,
	size_t ipsize, t_scan scan)
{
	struct tcphdr	hdr = TCP_SYN_HDR_TEMPLATE;

	(void)scan;
	hdr.th_dport = htons(scan_ctrl->port);
	hdr.th_seq = htonl(scan_ctrl->sequence);
	ft_memcpy(probe->buf + ipsize, &hdr, sizeof(hdr));
	if (scan_ctrl->payload_size)
		ft_memcpy(probe->buf + ipsize + sizeof(hdr), scan_ctrl->payload,
			scan_ctrl->payload_size);
}

static void	scan_build_probe_headers(t_packet *probe, t_scan_control *scan_ctrl,
	t_scan scan)
{
	enum e_ftscan_type	type = GET_SCAN_TYPE(scan);
	uint8_t				version = scan_ctrl->ip.family == AF_INET ? 4 : 6;
	uint8_t				protocol = ft_get_scan_protocol(type,
		scan_ctrl->ip.family);
	t_iph_args			ipargs = { .version = version, .protocol = protocol,
		.layer5_len = scan_ctrl->payload_size };
	size_t				size = scan_ctrl->ip.family == AF_INET ?
		sizeof(struct iphdr) : sizeof(struct ipv6hdr);

	ft_init_ip_header(probe->buf, &ipargs);
	switch (type)
	{
		case E_FTSCAN_ECHO_PING:
			if (protocol == IPPROTO_ICMP)
				add_echo_ping_v4_header(probe, scan_ctrl, size, scan);
			else
				add_echo_ping_v6_header(probe, scan_ctrl, size, scan);
			break;
		case E_FTSCAN_TCP_SYN:
			add_tcp_syn_header(probe, scan_ctrl, size, scan);
			break;
	}
}

/*
** ft_scan_send: Build a probe for the given scan and send it
**
** The sent_ts field of the t_scan_control structure will be overwritten to
** reset the timeout for this scan. It also will be used for RTT computation.
*/
int	ft_scan_send(t_scan scan)
{
	enum e_iphdr	iph;
	t_scan_control	*scan_ctrl;
	t_packet		probe = { 0 };
	struct timeval	sent_ts = { 0 };

	if (!(scan_ctrl = ft_get_scan(scan)))
		return (-1);
	++scan_ctrl->sequence;
	if (ft_scan_set_filter(scan))
		return (-1);
	iph = scan_ctrl->ip.family == AF_INET ? E_IH_V4 : E_IH_V6;
	scan_build_probe_headers(&probe, scan_ctrl, scan);
	ft_packet_init(&probe, iph, NULL);
	if (gettimeofday(&sent_ts, NULL) < 0)
	{
		ft_errno = -errno;
		return (-1);
	}
	if (ft_packet_send(scan_ctrl->sendfd, &scan_ctrl->ip, &probe, 1) < 0)
		return (-1);
	ft_memcpy(&scan_ctrl->sent_ts, &sent_ts, sizeof(sent_ts));
	return (0);
}
