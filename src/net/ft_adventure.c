/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adventure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:08:00 by yforeau           #+#    #+#             */
/*   Updated: 2022/03/14 16:19:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define COUNT_ADVENTURE_IP			16
#define COUNT_ADVENTURE_RANDOM_IP	128

/*
** ft_web_adventure: Returns a random ipv4 website found with an tcp syn scan
**
** dest: where the resulting ip is returned
** timeout: stop adventure when timeout is passed or when at least one address
** has been found (if NULL)
**
** Returns -1 on error, including timeout, and 0 if a host was found. In case
** of error ft_errno is set.
*/
/*
int	ft_web_adventure(t_ip *dest, struct timeval *timeout)
{
	
}
*/

static int	set_expiry(struct timeval *expiry, struct timeval *timeout)
{
	if (!timeout)
		return (0);
	if (gettimeofday(expiry, NULL) < 0)
	{
		ft_errno = -errno;
		return (-1);
	}
	if (ft_timeval_add(expiry, expiry, timeout) < 0)
		return (-1);
	return (0);
}

#define DEF_SCAN_TIMEOUT	{ 0, 500000 }	// 300ms

static int	set_timeout(struct timeval *scan_timeout, struct timeval *timeout)
{
	struct timeval	def_scan_timeout = DEF_SCAN_TIMEOUT;

	if (!timeout)
	{
		ft_memcpy(scan_timeout, &def_scan_timeout, sizeof(def_scan_timeout));
		return (0);
	}
	if (ft_timeval_div(scan_timeout, timeout, 2) < 0)
		return (-1);
	return (0);
}

static void	close_adventure_scans(t_pollsc scans[COUNT_ADVENTURE_RANDOM_IP],
	int all)
{
	for (int i = 0; i < COUNT_ADVENTURE_RANDOM_IP; ++i)
	{
		if (!scans[i].events && !all)
			continue;
		if (scans[i].scan >= 0)
			ft_scan_close(scans[i].scan);
		scans[i].events = 0;
		scans[i].scan = -1;
	}
}

static int	open_adventure_scans(t_ip rand_ip[COUNT_ADVENTURE_RANDOM_IP],
	t_pollsc scans[COUNT_ADVENTURE_RANDOM_IP], struct timeval *timeout)
{
	for (int i = 0; i < COUNT_ADVENTURE_RANDOM_IP; ++i)
	{
		if (scans[i].scan >= 0)
			continue;
		if (ft_ip_rand(rand_ip + i, 1, AF_INET, 0) < 0
			|| (scans[i].scan = ft_echo_ping_open(rand_ip + i, timeout) < 0))
			return (-1);
		scans[i].events = 0;
		if (ft_scan_send(scans[i].scan) < 0)
			return (-1);
	}
	return (0);
}

static int	get_results(t_ip *ip, int max,
	t_ip rand_ip[COUNT_ADVENTURE_RANDOM_IP],
	t_pollsc scans[COUNT_ADVENTURE_RANDOM_IP])
{
	t_scanres	result = { 0 };
	int			open_count = 0;

	for (int i = 0; i < COUNT_ADVENTURE_RANDOM_IP; ++i)
	{
		if (!scans[i].events)
			continue;
		if (ft_scan_result(&result, scans[i].scan) < 0)
			return (-1);
		ft_printf("open: %d - open_count: %d - max: %d - events: %d\n",
			result.open, open_count, max, scans[i].events);
		if (!result.open || open_count == max)
			continue;
		ft_memcpy(ip + open_count, rand_ip + i, sizeof(t_ip));
		++open_count;
	}
	close_adventure_scans(scans, 0);
	return (open_count);
}

#define DEF_SCANS	{\
	[0 ... COUNT_ADVENTURE_RANDOM_IP - 1] = { .scan = -1, .events = 0 }\
}

static int	ft_adventure_internal(t_ip *ip, int max, struct timeval *timeout)
{
	int				count = 0, ret = 0;
	struct timeval	expiry, scan_timeout;
	t_ip			rand_ip[COUNT_ADVENTURE_RANDOM_IP];
	t_pollsc		scans[COUNT_ADVENTURE_RANDOM_IP] = DEF_SCANS;

	if (set_timeout(&scan_timeout, timeout) < 0)
		return (-1);
	if (!(ret = open_adventure_scans(rand_ip, scans, &scan_timeout)))
		ret = set_expiry(&expiry, timeout);
	while (count < max && ret >= 0)
	{
		if ((ret = open_adventure_scans(rand_ip, scans, &scan_timeout)) < 0)
			break;
		if ((ret = ft_scan_poll(scans, COUNT_ADVENTURE_RANDOM_IP, NULL)) < 0
			|| (ret && (ret = get_results(ip, max, rand_ip, scans)) < 0))
			break;
		count += ret;
		max -= ret;
		if (timeout && (ret = ft_timeval_is_expired(NULL, &expiry)))
			break;
	}
	close_adventure_scans(scans, 1);
	return (ret < 0 ? -1 : count);
}

/*
** ft_adventure: Returns a random ipv4 host found with an echo ping scan
**
** dest: where the resulting ip is returned
** timeout: stop adventure when timeout is passed or when at least one address
** has been found (if NULL)
**
** Returns -1 on error, including timeout, and 0 if a host was found. In case
** of error ft_errno is set.
*/
int	ft_adventure(t_ip *dest, struct timeval *timeout)
{
#ifdef THEAD_SAFE
	static __thread int		count = 0;
	static __thread t_ip	ip[COUNT_ADVENTURE_IP] = { 0 };
#else
	static int				count = 0;
	static t_ip				ip[COUNT_ADVENTURE_IP] = { 0 };
#endif
	int						req = COUNT_ADVENTURE_IP - count, res;
	
	res = ft_adventure_internal(ip + count, req, timeout);
	if (res < 0 || (!res && !count))
		return (-1);
	count += res;
	ft_memcpy(dest, ip + --count, sizeof(t_ip));
	return (0);
}
