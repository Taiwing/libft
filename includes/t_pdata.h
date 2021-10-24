/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pdata.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:56:33 by yforeau           #+#    #+#             */
/*   Updated: 2021/10/24 13:17:01 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PDATA_H
# define T_PDATA_H

// Size for the default static buffer (dbuf)
# define BLOCK_SIZE 4096

# include <stddef.h>
# include <stdint.h>

/*
** PDATA flags:
**
** PDATA_ALLOC: the buffer is allocated at start else it is static
** PDATA_NOLIMIT: buffer limit is not known
** PDATA_STOP: if buffer limit is reached stop
** PDATA_FLUSH: if limit is reached continue by flushing buffer else realloc
** PDATA_RETBUF: return buffer at the end else print it
**
** Notes: Some flags are incompatible. Here's the list below.
**
** PDATA_ALLOC | PDATA_NOLIMIT: The buffer is allocated at the start so its
** length is known. NOLIMIT only makes sense if the buffer is user defined and
** of unknown length. NOLIMIT will be ignored.
**
** PDATA_NOLIMIT | (PDATA_STOP | PDATA_FLUSH): The STOP/CONTINUE bit is only
** used if the buffer limit is reached. The ft_printf functions will never STOP
** or FLUSH if NOLIMIT is set. STOP and FLUSH will be ignored.
** 
** PDATA_STOP | PDATA_FLUSH: The FLUSH/REALLOC bit is only looked at if STOP is
** unset because they represent the action taken if LIMIT is reached and if we
** must continue. FLUSH will be ignored.
**
** PDATA_FLUSH | PDATA_RETBUF: FLUSH will print the output and clean the buffer
** (ie: free the buffer if it has been allocated). It does not make sense to
** print when the buffer is reached, empty it and only return the end of the
** buffer unprinted. It could be done but it is as incoherent as it is useless.
** So FLUSH implies PRINT. RETBUF will be ignored.
*/

# define PDATA_ALLOC	0x01 // 0 --> STATIC
# define PDATA_NOLIMIT	0x02 // 0 --> HASLIMIT
# define PDATA_STOP		0x04 // 0 --> CONTINUE
# define PDATA_FLUSH	0x08 // 0 --> REALLOC
# define PDATA_RETBUF	0x10 // 0 --> PRINT

/*
** e_pmodes: Print Modes
**
** These are the valid print modes consisting of predefined combinations of
** flags and each corresponding to one or more print functions. This is needed
** because as noted above, some combination of flags are invalid and will lead
** to errors.
*/

enum e_pmodes {
	PMODE_CLASSIC = 0,								// ft_printf/ft_dprintf
	PMODE_NOALLOC = PDATA_FLUSH,					// ft_zprintf/ft_dzprintf ??? (TODO)
	PMODE_NOLIMIT = PDATA_NOLIMIT | PDATA_RETBUF,	// ft_sprintf
	PMODE_BUFLIMIT = PDATA_STOP | PDATA_RETBUF,		// ft_snprintf
	PMODE_BUFALLOC = PDATA_ALLOC | PDATA_RETBUF,	// ft_asprintf
};

/*
** t_pdata: Print Data Structure
**
** This is the main data buffer structure for ft_printf functions. It can set as
** static, allocated, resizable or fixed buffer. The versatility in its
** configuration is what allows multiple versions of ft_printf to exist.
**
** flags: PDATA flags for modifying buffer's behavior
** buf: is a pointer set to the underlying real buffer
** sbuf: static buffer, or user buffer treated as static
** abuf: allocated buffer if PDATA_ALLOC or reallocating on limit
** dbuf: default static buffer of BLOCK_SIZE
** bufsize: size of the real buffer (ignored if NOLIMIT)
** n: length of data contained in buffer (or error if n < 0)
** flushed: length of data flushed (added to final n)
*/
typedef struct	s_pdata
{
	uint8_t		flags;
	char		*buf;
	char		*sbuf;
	char		*abuf;
	char		dbuf[BLOCK_SIZE];
	size_t		bufsize;
	int			fd;
	int			n;
	int			flushed;
}				t_pdata;

void			pdata_add(t_pdata *data, char *add, int c, size_t size);
void			pdata_print(t_pdata *data);
void			pdata_local_set_buf(t_pdata *loc);
void			pdata_set_buf(t_pdata *data,
					char *userbuf, size_t userbuf_size);
void			pdata_init(t_pdata *data, enum e_pmodes pmode, int fd);

#endif
