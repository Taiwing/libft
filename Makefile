############################## COMPILE VAR #####################################

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		=	-g
HDIR		=	includes
SRCDIR		=	src
HFLAGS		=	-I $(HDIR)
NAME		=	libft.a

############################## SOURCES #########################################

FT_GETOPTDIR	=	ft_getopt

SRCC			=	ft_atoi.c\
					ft_bzero.c\
					ft_isalnum.c\
					ft_isalpha.c\
					ft_isascii.c\
					ft_isdigit.c\
					ft_isprint.c\
					ft_itoa.c\
					ft_lst_at.c\
					ft_lst_find.c\
					ft_lst_foreach.c\
					ft_lst_foreach_if.c\
					ft_lst_last.c\
					ft_lst_merge.c\
					ft_lst_move_front.c\
					ft_lst_push_back.c\
					ft_lst_push_front.c\
					ft_lst_push_params.c\
					ft_lst_remove_if.c\
					ft_lst_reverse.c\
					ft_lst_size.c\
					ft_lst_sort.c\
					ft_lstadd.c\
					ft_lstdel.c\
					ft_lstdelone.c\
					ft_lstiter.c\
					ft_lstmap.c\
					ft_lstnew.c\
					ft_memalloc.c\
					ft_memccpy.c\
					ft_memchr.c\
					ft_memcmp.c\
					ft_memcpy.c\
					ft_memdel.c\
					ft_memmove.c\
					ft_memset.c\
					ft_print_words_tables.c\
					ft_print_words_tables_fd.c\
					ft_putchar.c\
					ft_putchar_fd.c\
					ft_putendl.c\
					ft_putendl_fd.c\
					ft_putnbr.c\
					ft_putnbr_fd.c\
					ft_putstr.c\
					ft_putstr_fd.c\
					ft_split_whitespaces.c\
					ft_stradd.c\
					ft_strcat.c\
					ft_strchr.c\
					ft_strclr.c\
					ft_strcmp.c\
					ft_strcpy.c\
					ft_strcut.c\
					ft_strdel.c\
					ft_strdup.c\
					ft_strequ.c\
					ft_striter.c\
					ft_striteri.c\
					ft_strjoin.c\
					ft_strlcat.c\
					ft_strlen.c\
					ft_strmap.c\
					ft_strmapi.c\
					ft_strncat.c\
					ft_strncmp.c\
					ft_strncpy.c\
					ft_strndup.c\
					ft_strnequ.c\
					ft_strnew.c\
					ft_strnstr.c\
					ft_strrchr.c\
					ft_strsplit.c\
					ft_strstr.c\
					ft_strsub.c\
					ft_strtrim.c\
					ft_tolower.c\
					ft_toupper.c\
					get_next_line.c\

FT_GETOPTC		=	ft_getopt.c\
					get_next_option_argument.c\
					get_short_option.c\
					getopt_errors.c\
					getopt_long_errors.c\
					init_getopt.c\
					permute_order.c\
					process_long_option.c\

ODIR			=	obj
OBJ				=	$(patsubst %.c,%.o,$(FT_GETOPTC))\
					$(patsubst %.c,%.o,$(SRCC))\

vpath			%.o	$(ODIR)
vpath			%.h	$(HDIR)
vpath			%.c	$(SRCDIR)/$(FT_GETOPTDIR)
vpath			%.c	$(SRCDIR)

############################## BUILD ###########################################

all: $(NAME)

$(NAME): $(ODIR) $(OBJ)
	ar rc $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ))
	ranlib $@

ft_atoi.o: libft.h get_next_line.h ft_getopt.h
ft_bzero.o: libft.h get_next_line.h ft_getopt.h
ft_getopt.o: get_next_option_argument.h ft_getopt.h get_short_option.h
get_next_option_argument.o: permute_order.h ft_getopt.h process_long_option.h\
	libft.h get_next_line.h
get_short_option.o: libft.h get_next_line.h ft_getopt.h getopt_errors.h
getopt_errors.o: libft.h get_next_line.h ft_getopt.h
getopt_long_errors.o: getopt_errors.h ft_getopt.h libft.h get_next_line.h
init_getopt.o: ft_getopt.h
permute_order.o: ft_getopt.h
process_long_option.o: libft.h get_next_line.h ft_getopt.h getopt_errors.h
ft_isalnum.o: libft.h get_next_line.h ft_getopt.h
ft_isalpha.o: libft.h get_next_line.h ft_getopt.h
ft_isascii.o: libft.h get_next_line.h ft_getopt.h
ft_isdigit.o: libft.h get_next_line.h ft_getopt.h
ft_isprint.o: libft.h get_next_line.h ft_getopt.h
ft_itoa.o: libft.h get_next_line.h ft_getopt.h
ft_lst_at.o: libft.h get_next_line.h ft_getopt.h
ft_lst_find.o: libft.h get_next_line.h ft_getopt.h
ft_lst_foreach.o: libft.h get_next_line.h ft_getopt.h
ft_lst_foreach_if.o: libft.h get_next_line.h ft_getopt.h
ft_lst_last.o: libft.h get_next_line.h ft_getopt.h
ft_lst_merge.o: libft.h get_next_line.h ft_getopt.h
ft_lst_move_front.o: libft.h get_next_line.h ft_getopt.h
ft_lst_push_back.o: libft.h get_next_line.h ft_getopt.h
ft_lst_push_front.o: libft.h get_next_line.h ft_getopt.h
ft_lst_push_params.o: libft.h get_next_line.h ft_getopt.h
ft_lst_remove_if.o: libft.h get_next_line.h ft_getopt.h
ft_lst_reverse.o: libft.h get_next_line.h ft_getopt.h
ft_lst_size.o: libft.h get_next_line.h ft_getopt.h
ft_lst_sort.o: libft.h get_next_line.h ft_getopt.h
ft_lstadd.o: libft.h get_next_line.h ft_getopt.h
ft_lstdel.o: libft.h get_next_line.h ft_getopt.h
ft_lstdelone.o: libft.h get_next_line.h ft_getopt.h
ft_lstiter.o: libft.h get_next_line.h ft_getopt.h
ft_lstmap.o: libft.h get_next_line.h ft_getopt.h
ft_lstnew.o: libft.h get_next_line.h ft_getopt.h
ft_memalloc.o: libft.h get_next_line.h ft_getopt.h
ft_memccpy.o: libft.h get_next_line.h ft_getopt.h
ft_memchr.o: libft.h get_next_line.h ft_getopt.h
ft_memcmp.o: libft.h get_next_line.h ft_getopt.h
ft_memcpy.o: libft.h get_next_line.h ft_getopt.h
ft_memdel.o: libft.h get_next_line.h ft_getopt.h
ft_memmove.o: libft.h get_next_line.h ft_getopt.h
ft_memset.o: libft.h get_next_line.h ft_getopt.h
ft_print_words_tables.o: libft.h get_next_line.h ft_getopt.h
ft_print_words_tables_fd.o: libft.h get_next_line.h ft_getopt.h
ft_putchar.o: libft.h get_next_line.h ft_getopt.h
ft_putchar_fd.o: libft.h get_next_line.h ft_getopt.h
ft_putendl.o: libft.h get_next_line.h ft_getopt.h
ft_putendl_fd.o: libft.h get_next_line.h ft_getopt.h
ft_putnbr.o: libft.h get_next_line.h ft_getopt.h
ft_putnbr_fd.o: libft.h get_next_line.h ft_getopt.h
ft_putstr.o: libft.h get_next_line.h ft_getopt.h
ft_putstr_fd.o: libft.h get_next_line.h ft_getopt.h
ft_split_whitespaces.o: libft.h get_next_line.h ft_getopt.h
ft_stradd.o: libft.h get_next_line.h ft_getopt.h
ft_strcat.o: libft.h get_next_line.h ft_getopt.h
ft_strchr.o: libft.h get_next_line.h ft_getopt.h
ft_strclr.o: libft.h get_next_line.h ft_getopt.h
ft_strcmp.o: libft.h get_next_line.h ft_getopt.h
ft_strcpy.o: libft.h get_next_line.h ft_getopt.h
ft_strcut.o: libft.h get_next_line.h ft_getopt.h
ft_strdel.o: libft.h get_next_line.h ft_getopt.h
ft_strdup.o: libft.h get_next_line.h ft_getopt.h
ft_strequ.o: libft.h get_next_line.h ft_getopt.h
ft_striter.o: libft.h get_next_line.h ft_getopt.h
ft_striteri.o: libft.h get_next_line.h ft_getopt.h
ft_strjoin.o: libft.h get_next_line.h ft_getopt.h
ft_strlcat.o: libft.h get_next_line.h ft_getopt.h
ft_strlen.o: libft.h get_next_line.h ft_getopt.h
ft_strmap.o: libft.h get_next_line.h ft_getopt.h
ft_strmapi.o: libft.h get_next_line.h ft_getopt.h
ft_strncat.o: libft.h get_next_line.h ft_getopt.h
ft_strncmp.o: libft.h get_next_line.h ft_getopt.h
ft_strncpy.o: libft.h get_next_line.h ft_getopt.h
ft_strndup.o: libft.h get_next_line.h ft_getopt.h
ft_strnequ.o: libft.h get_next_line.h ft_getopt.h
ft_strnew.o: libft.h get_next_line.h ft_getopt.h
ft_strnstr.o: libft.h get_next_line.h ft_getopt.h
ft_strrchr.o: libft.h get_next_line.h ft_getopt.h
ft_strsplit.o: libft.h get_next_line.h ft_getopt.h
ft_strstr.o: libft.h get_next_line.h ft_getopt.h
ft_strsub.o: libft.h get_next_line.h ft_getopt.h
ft_strtrim.o: libft.h get_next_line.h ft_getopt.h
ft_tolower.o: libft.h get_next_line.h ft_getopt.h
ft_toupper.o: libft.h get_next_line.h ft_getopt.h
get_next_line.o: libft.h get_next_line.h ft_getopt.h
%.o: %.c
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
