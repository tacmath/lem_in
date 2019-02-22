# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/08/13 13:17:34 by lperron      #+#   ##    ##    #+#        #
#    Updated: 2019/02/21 15:00:22 by mtaquet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SRCDIRLC= ./srcs/libc/
SRCDIRSU= ./srcs/supp/
SRCDIRBONUS= ./srcs/bonus/
SRCDIRPERS= ./srcs/perso/
SRCDIRPRINTF= ./srcs/ft_printf/
FILESLC= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_strrchr.c ft_strstr.c ft_tolower.c ft_toupper.c
FILESSU= ft_itoa.c ft_memalloc.c ft_memdel.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strclr.c ft_strdel.c  ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strmap.c ft_strmapi.c ft_strnequ.c ft_strnew.c ft_strsplit.c ft_strsub.c ft_strtrim.c
FILESBONUS= ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c
FILESPERS= ft_realloc.c ft_sort_integer_table.c ft_split_whitespaces.c ft_str_is_alpha.c ft_str_is_numeric.c ft_swap.c ft_max.c ft_min.c ft_abs.c ft_itoa_base.c ft_two_s_complement.c ft_iterative_power.c ft_strjoin_free.c ft_dbl_truncate.c ft_dbl_get_deci.c uni.c ft_dtoa.c ft_dtoat.c ft_uitoa_base.c ft_strchri.c ft_ischarset.c ft_litoa.c ft_luitoa_base.c ft_strtolower.c ft_str_replace.c ft_uitoa_basem.c ft_ldtoa.c ft_ldtoat.c ft_ldbl_truncate.c ft_ldbl_get_deci.c ft_jitoa.c ft_juitoa_base.c ft_strsub_free.c ft_strjoin_free.c ft_strjoin_mult.c ft_super_free.c get_next_line.c
FILESPRINTF= bin_handler.c float_handler.c ft_format_numb.c ft_parser.c ft_printf_add.c ft_printf.c functions.c int_handler.c int_handler2.c percent_handler.c string_handler.c unico_handler.c unsigned_handler.c utils.c widthprec.c
FILESINC= libft.h ft_printf.h
INCDIR= ./includes/
FILES= $(FILESLC) $(FILESSU) $(FILESBONUS) $(FILESPERS)
SRC= $(addprefix $(SRCDIRLC),$(FILESLC)) $(addprefix $(SRCDIRSU),$(FILESSU)) $(addprefix $(SRCDIRBONUS),$(FILESBONUS)) $(addprefix $(SRCDIRPERS),$(FILESPERS)) $(addprefix $(SRCDIRPRINTF),$(FILESPRINTF))
INC= $(addprefix $(INCDIR),$(FILESINC))
OBJ= $(SRC:.c=.o)
NAME= libft.a
CFLAGS= -Wall -Werror -Wextra
CC= gcc

all: $(NAME)

%.o: %.c $(INC)
	$(CC) -c -o $@ $< -I $(INCDIR) $(CFLAGS)

$(NAME): $(OBJ) $(INC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
re: fclean $(NAME)	
