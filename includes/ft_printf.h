/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:26:09 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/25 06:31:31 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>

int	ft_printf(const char *format, ...);
int	ft_dprintf(int fd, const char *format, ...);
int	ft_sprintf(char *str, const char *format, ...);
int	ft_snprintf(char *str, int size, const char *format, ...);
int	ft_asprintf(char **str, const char *format, ...);
int	ft_zprintf(const char *format, ...);
int	ft_dzprintf(int fd, const char *format, ...);

#endif
