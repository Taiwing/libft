############################## COMPILE VAR #####################################

CC			=	gcc
#CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address,undefined
HDIR		=	includes
SRCDIR		=	src
HFLAGS		=	-I $(HDIR)
NAME		=	libft.a

############################## SOURCES #########################################

FT_GETOPTDIR	=	ft_getopt
FT_LSDIR		=	ft_ls
MATHDIR			=	math
FT_THREADDIR	=	ft_thread
NETDIR			=	net
FT_PRINTFDIR	=	ft_printf
CHARDIR			=	char
BINTDIR			=	bint
FT_COLLECTORDIR	=	ft_collector
STRDIR			=	str
RANDDIR			=	rand
INTDIR			=	int
WTDIR			=	wt
T_LSTDIR		=	t_lst
TIMEDIR			=	time
UNIXDIR			=	unix
MEMORYDIR		=	memory

SRCC			=	get_next_line.c\
					ft_errno.c\
					get_next_line_utils.c\
					ft_swap_p.c\

FT_GETOPTC		=	process_long_option.c\
					get_next_option_argument.c\
					ft_getopt.c\
					getopt_long_errors.c\
					get_short_option.c\
					permute_order.c\
					init_getopt.c\
					getopt_errors.c\

FT_LSC			=	ft_ls_files.c\

MATHC			=	ft_sqrt.c\

FT_THREADC		=	ft_thread_join.c\
					ft_thread_create.c\
					ft_thread_self.c\
					ft_mutex.c\
					ft_thread_error.c\

NETC			=	scan_list.c\
					ft_get_ip.c\
					ft_net_listiface.c\
					ft_ip_str.c\
					ft_scan_send.c\
					ft_echo_ping_parse_reply.c\
					print_headers.c\
					ft_packet_send.c\
					ip_headers.c\
					sockets.c\
					ip.c\
					ft_scan_recv.c\
					ft_packet_filter_layer4.c\
					ft_packet_filter_echo_ping.c\
					ft_packet_filter_icmp_layer4.c\
					ft_scan_poll.c\
					ft_tcp_syn_parse_reply.c\
					ft_packet_filter_tcp_syn.c\
					ft_ip_rand.c\
					layer4_headers.c\
					ft_scan_open.c\
					ft_scans.c\
					ft_net_ifaces.c\
					packet.c\
					ft_scan_close.c\
					ft_scan_set_filter.c\

FT_PRINTFC		=	ft_printf_internal.c\
					pdata_add.c\
					itoa_unsigned.c\
					itoa.c\
					basic_conversions.c\
					float_formats.c\
					get_conv.c\
					itoa_cast.c\
					get_flags.c\
					fetch.c\
					itoa_signed.c\
					ft_printf_utils.c\
					parser.c\
					uni_conversions.c\
					format_data.c\
					efg_conversions.c\
					ft_printf.c\
					tab_conversion.c\
					pdata.c\

CHARC			=	ft_isdigit.c\
					ft_isascii.c\
					ft_isprint.c\
					ft_isalpha.c\
					ft_tolower.c\
					ft_isalnum.c\
					ft_putchar.c\
					ft_putchar_fd.c\
					ft_isspace.c\
					ft_toupper.c\

BINTC			=	bint_utils_1.c\
					dragon42.c\
					bint_divmod_max9.c\
					bintset.c\
					bint_mod.c\
					bint_add.c\
					dragon4.c\
					log_and_ceil.c\
					bint_shift.c\
					bint_mult.c\
					bint_sub.c\
					bint_mathconsts.c\
					bintcmp.c\
					bint_mult_by.c\
					bint_prime.c\
					bint_utils_2.c\
					bint_divide.c\

FT_COLLECTORC		=	ft_first_exit.c\
					ft_dir_collector.c\
					ft_heap_collector.c\
					ft_exit.c\
					ft_secmalloc.c\
					ft_collector.c\

STRC			=	ft_strclr.c\
					ft_strchr.c\
					ft_strmap.c\
					ft_stradd.c\
					ft_putendl_fd.c\
					ft_strlcat.c\
					ft_strdup.c\
					ft_strcmp.c\
					ft_strmapi.c\
					ft_putendl.c\
					ft_strdel.c\
					ft_putstr.c\
					ft_strnequ.c\
					ft_putstr_fd.c\
					ft_strncmp.c\
					ft_strncat.c\
					ft_strrm.c\
					ft_strjoin.c\
					ft_ignore_case_strncmp.c\
					ft_strncpy.c\
					ft_strequ.c\
					ft_strsplit.c\
					ft_strndup.c\
					ft_strnstr.c\
					ft_strnew.c\
					ft_strcut.c\
					ft_striteri.c\
					ft_strcat.c\
					ft_ignore_case_strcmp.c\
					ft_strtrim.c\
					ft_strlen.c\
					ft_strrchr.c\
					ft_strcpy.c\
					ft_strsub.c\
					ft_strstr.c\
					ft_striter.c\

RANDC			=	ft_rand_source.c\

INTC			=	ft_intlen.c\
					ft_atoi.c\
					ft_putnbr_fd.c\
					ft_atoi_forward.c\
					ft_putnbr.c\
					ft_rand.c\
					ft_secatoi.c\
					ft_itoa.c\

WTC				=	ft_wtlen.c\
					ft_wtdup.c\
					ft_wtfree.c\
					ft_split_whitespaces.c\
					ft_print_words_tables.c\
					ft_print_words_tables_fd.c\

T_LSTC			=	ft_lstdelone.c\
					ft_lst_foreach_if.c\
					ft_lstnew.c\
					ft_lst_move_front.c\
					ft_lst_push_back.c\
					ft_lst_last.c\
					ft_lstdel.c\
					ft_lstiter.c\
					ft_lst_move_back.c\
					ft_lst_quicksort.c\
					ft_lst_move_to_back.c\
					ft_lstmap.c\
					ft_lst_at.c\
					ft_lst_foreach.c\
					ft_lst_find_index.c\
					ft_lstadd.c\
					ft_lst_reverse.c\
					ft_lst_sort.c\
					ft_lst_move_to_front.c\
					ft_lst_size.c\
					ft_lst_push_params.c\
					ft_lst_pop.c\
					ft_lst_discard.c\
					ft_lst_remove_if.c\
					ft_lst_find.c\
					ft_lst_pop_if.c\
					ft_lst_merge.c\
					ft_lst_push_front.c\
					ft_lst_sorted_insert.c\

TIMEC			=	ft_timeval_is_expired.c\
					ft_timeval_is_zero.c\
					ft_timeval_ops.c\

UNIXC			=	ft_exec_name.c\

MEMORYC			=	ft_memmove.c\
					ft_memcmp.c\
					ft_memcpy.c\
					ft_memalloc.c\
					ft_memccpy.c\
					ft_memswap.c\
					ft_bzero.c\
					ft_memchr.c\
					ft_memset.c\
					ft_memdel.c\
					ft_memdup.c\

ODIR			=	obj
OBJ				=	$(patsubst %.c,%.o,$(FT_GETOPTC))\
					$(patsubst %.c,%.o,$(FT_LSC))\
					$(patsubst %.c,%.o,$(MATHC))\
					$(patsubst %.c,%.o,$(FT_THREADC))\
					$(patsubst %.c,%.o,$(NETC))\
					$(patsubst %.c,%.o,$(FT_PRINTFC))\
					$(patsubst %.c,%.o,$(CHARC))\
					$(patsubst %.c,%.o,$(BINTC))\
					$(patsubst %.c,%.o,$(FT_COLLECTORC))\
					$(patsubst %.c,%.o,$(STRC))\
					$(patsubst %.c,%.o,$(RANDC))\
					$(patsubst %.c,%.o,$(INTC))\
					$(patsubst %.c,%.o,$(WTC))\
					$(patsubst %.c,%.o,$(T_LSTC))\
					$(patsubst %.c,%.o,$(TIMEC))\
					$(patsubst %.c,%.o,$(UNIXC))\
					$(patsubst %.c,%.o,$(MEMORYC))\
					$(patsubst %.c,%.o,$(SRCC))\

vpath			%.o	$(ODIR)
vpath			%.h	$(HDIR)
vpath			%.c	$(SRCDIR)/$(FT_GETOPTDIR)
vpath			%.c	$(SRCDIR)/$(FT_LSDIR)
vpath			%.c	$(SRCDIR)/$(MATHDIR)
vpath			%.c	$(SRCDIR)/$(FT_THREADDIR)
vpath			%.c	$(SRCDIR)/$(NETDIR)
vpath			%.c	$(SRCDIR)/$(FT_PRINTFDIR)
vpath			%.c	$(SRCDIR)/$(CHARDIR)
vpath			%.c	$(SRCDIR)/$(BINTDIR)
vpath			%.c	$(SRCDIR)/$(FT_COLLECTORDIR)
vpath			%.c	$(SRCDIR)/$(STRDIR)
vpath			%.c	$(SRCDIR)/$(RANDDIR)
vpath			%.c	$(SRCDIR)/$(INTDIR)
vpath			%.c	$(SRCDIR)/$(WTDIR)
vpath			%.c	$(SRCDIR)/$(T_LSTDIR)
vpath			%.c	$(SRCDIR)/$(TIMEDIR)
vpath			%.c	$(SRCDIR)/$(UNIXDIR)
vpath			%.c	$(SRCDIR)/$(MEMORYDIR)
vpath			%.c	$(SRCDIR)

############################## BUILD ###########################################

all: $(NAME)

$(NAME): $(ODIR) $(OBJ)
	ar rc $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ))
	ranlib $@

process_long_option.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h getopt_errors.h
get_next_option_argument.o: permute_order.h ft_getopt.h process_long_option.h\
	libft.h ft_errno.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
ft_getopt.o: get_next_option_argument.h ft_getopt.h get_short_option.h
getopt_long_errors.o: getopt_errors.h ft_getopt.h libft.h ft_errno.h\
	ft_printf.h bint.h network.h ft_collector.h ft_exit.h
get_short_option.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h getopt_errors.h
permute_order.o: ft_getopt.h
init_getopt.o: ft_getopt.h
getopt_errors.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
get_next_line.o: get_next_line.h libft.h ft_errno.h ft_getopt.h ft_printf.h\
	bint.h network.h ft_collector.h ft_exit.h
ft_ls_files.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_errno.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_thread_join.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_thread_create.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_thread_self.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_mutex.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_thread_error.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
scan_list.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_get_ip.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_net_listiface.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_ip_str.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_scan_send.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_echo_ping_parse_reply.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
print_headers.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_packet_send.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ip_headers.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
sockets.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ip.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_scan_recv.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_packet_filter_layer4.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_packet_filter_echo_ping.o: libft.h ft_errno.h ft_getopt.h ft_printf.h\
	bint.h network.h ft_collector.h ft_exit.h
ft_packet_filter_icmp_layer4.o: libft.h ft_errno.h ft_getopt.h ft_printf.h\
	bint.h network.h ft_collector.h ft_exit.h
ft_scan_poll.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_tcp_syn_parse_reply.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_packet_filter_tcp_syn.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_ip_rand.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
layer4_headers.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_scan_open.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_scans.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_net_ifaces.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
packet.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_scan_close.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_scan_set_filter.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_printf_internal.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h\
	ft_errno.h ft_getopt.h ft_printf.h bint.h network.h ft_collector.h\
	ft_exit.h
pdata_add.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h ft_errno.h\
	ft_getopt.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
itoa_unsigned.o: ft_printf_internal.h t_pdata.h dragon4.h
itoa.o: ft_printf_internal.h t_pdata.h dragon4.h
basic_conversions.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h\
	ft_errno.h ft_getopt.h ft_printf.h bint.h network.h ft_collector.h\
	ft_exit.h
float_formats.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h ft_errno.h\
	ft_getopt.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
get_conv.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h ft_errno.h\
	ft_getopt.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
itoa_cast.o: ft_printf_internal.h t_pdata.h dragon4.h
get_flags.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h ft_errno.h\
	ft_getopt.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
fetch.o: ft_printf_internal.h t_pdata.h dragon4.h
itoa_signed.o: ft_printf_internal.h t_pdata.h dragon4.h
parser.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h ft_errno.h\
	ft_getopt.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
uni_conversions.o: ft_printf_internal.h t_pdata.h dragon4.h
format_data.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h ft_errno.h\
	ft_getopt.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
efg_conversions.o: ft_printf_internal.h t_pdata.h dragon4.h log_and_ceil.h
ft_printf.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h ft_errno.h\
	ft_getopt.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
tab_conversion.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h ft_errno.h\
	ft_getopt.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
pdata.o: ft_printf_internal.h t_pdata.h dragon4.h libft.h ft_errno.h\
	ft_getopt.h ft_printf.h bint.h network.h ft_collector.h ft_exit.h
ft_isdigit.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_isascii.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_isprint.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_isalpha.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_tolower.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_isalnum.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_putchar.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_putchar_fd.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_isspace.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_toupper.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
bint_utils_1.o: bint.h
dragon42.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h dragon4.h log_and_ceil.h
bint_divmod_max9.o: bint.h
bintset.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
bint_mod.o: bint.h
bint_add.o: bint.h
dragon4.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h dragon4.h log_and_ceil.h
log_and_ceil.o: bint.h
bint_shift.o: bint.h
bint_mult.o: bint.h
bint_sub.o: bint.h
bint_mathconsts.o: bint.h
bintcmp.o: bint.h
bint_mult_by.o: bint.h
bint_prime.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
bint_utils_2.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
bint_divide.o: bint.h
ft_first_exit.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_dir_collector.o: ft_collector.h ft_exit.h
ft_heap_collector.o: ft_collector.h ft_exit.h
ft_exit.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h ft_printf_internal.h t_pdata.h dragon4.h
ft_secmalloc.o: ft_collector.h ft_exit.h
ft_collector.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strclr.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strchr.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strmap.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_stradd.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_putendl_fd.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strlcat.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strdup.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strcmp.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strmapi.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_putendl.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strdel.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_putstr.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strnequ.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_putstr_fd.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strncmp.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strncat.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strrm.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strjoin.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_ignore_case_strncmp.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_strncpy.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strequ.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strsplit.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strndup.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strnstr.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strnew.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strcut.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_striteri.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strcat.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_ignore_case_strcmp.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_strtrim.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strlen.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strrchr.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strcpy.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strsub.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_strstr.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_striter.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
get_next_line_utils.o: get_next_line.h libft.h ft_errno.h ft_getopt.h\
	ft_printf.h bint.h network.h ft_collector.h ft_exit.h
ft_atoi.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_putnbr_fd.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_putnbr.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_rand.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_secatoi.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_itoa.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_wtdup.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_wtfree.o: ft_collector.h ft_exit.h
ft_split_whitespaces.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_print_words_tables.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_print_words_tables_fd.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lstdelone.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_foreach_if.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lstnew.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_move_front.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lst_push_back.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lst_last.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lstdel.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lstiter.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_move_back.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lst_quicksort.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lst_move_to_back.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lstmap.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_at.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_foreach.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_find_index.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lstadd.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_reverse.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_sort.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_move_to_front.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lst_size.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_push_params.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lst_pop.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_discard.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_remove_if.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lst_find.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_pop_if.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_merge.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_lst_push_front.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_lst_sorted_insert.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_timeval_is_expired.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_timeval_is_zero.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h\
	network.h ft_collector.h ft_exit.h
ft_timeval_ops.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_exec_name.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memmove.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memcmp.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memcpy.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memalloc.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memccpy.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memswap.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_bzero.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memchr.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memset.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memdel.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
ft_memdup.o: libft.h ft_errno.h ft_getopt.h ft_printf.h bint.h network.h\
	ft_collector.h ft_exit.h
%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) -c $(CFLAGS) $< $(HFLAGS) -o $(ODIR)/$@

$(ODIR):
	mkdir -p $@

############################## CLEANUP #########################################

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
