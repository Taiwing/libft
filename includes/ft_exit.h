/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:36:36 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/03 16:04:47 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXIT_H
# define FT_EXIT_H

# define EXIT_MSG_MAX	2048

enum e_fe_status	{ FIRST_EXIT_OFF = 0, FIRST_EXIT_ON, FIRST_EXIT_FILLED };

/*
** t_exit_args: exit arguments
**
** status: defines if and how the first exit is going to be used
** err: buffer storing error message
** errcode: corresponds to ft_exit argument
** ret: corresponds to ft_exit argument
*/
typedef struct			s_exit_args
{
	enum e_fe_status	status;
	char				err[EXIT_MSG_MAX + 1];
	int					errcode;
	int					ret;
}						t_exit_args;

/*
** Global instance of t_exit_args for ft_get_first_exit()
*/
extern t_exit_args	g_first_exit;

typedef void		(*t_atexitf)(void);

char				*ft_exitmsg(char *str);
void				ft_atexit(t_atexitf handler);
void				ft_exit(char *err, int errcode, int ret);
void				ft_first_exit(void);
void				ft_set_first_exit(char *err, int errcode, int ret);
void				ft_get_first_exit(char **err, int *errcode, int *ret);

#endif
