/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:36:36 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/02 17:38:20 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXIT_H
# define FT_EXIT_H

typedef void			(*t_atexitf)(void);

char					*ft_exitmsg(char *str);
void					ft_atexit(t_atexitf handler);
void					ft_exit(char *err, int errcode, int ret);

#endif
