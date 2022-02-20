/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_set_filter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:29:35 by yforeau           #+#    #+#             */
/*   Updated: 2022/02/19 22:33:40 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_tcp_syn_set_filter(uint16_t id)
{
	t_scan_control	*scan_ctrl = g_scan_list[E_FTSCAN_TCP_SYN][id];
	t_filter_spec	spec = {
		.min_src_port = scan_ctrl->port,
		.max_src_port = scan_ctrl->port,
		.min_dst_port = DEF_FTSCAN_TCP_SYN_PORT,
		.max_dst_port = DEF_FTSCAN_TCP_SYN_PORT,
		.src = &scan_ctrl->ip,
	};

	return (ft_packet_filter_tcp_syn(scan_ctrl->recvfd, &spec));
}

static int		ft_echo_ping_set_filter(uint16_t id)
{
	t_scan_control	*scan_ctrl = g_scan_list[E_FTSCAN_ECHO_PING][id];
	t_filter_spec	spec = {
		.icmp_echo_id = id,	//TODO: use both type and id for the echo id
		.icmp_echo_sequence = scan_ctrl->sequence,
		.src = &scan_ctrl->ip,
	};

	return (ft_packet_filter_echo_ping(scan_ctrl->recvfd, &spec));
}

int				ft_scan_set_filter(enum e_ftscan_type type, uint16_t id)
{
	switch (type)
	{
		case E_FTSCAN_ECHO_PING: return (ft_echo_ping_set_filter(id));	break;
		case E_FTSCAN_TCP_SYN: return (ft_tcp_syn_set_filter(id));		break;
	}
	return (-1);	// Once again, WTF gcc ?
}
