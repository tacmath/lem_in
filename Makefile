# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/05 12:24:50 by mtaquet      #+#   ##    ##    #+#        #
#    Updated: 2019/04/17 15:24:14 by mtaquet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = lem-in
LIBDIR = libft/
SRCDIR = srcs/
INCDIR = includes/
LIBFILES = libft.a
SRCFILES = main.c\
		   room.c\
		   connection.c\
		   utils.c\
		   path.c\
		   path2.c\
		   get_path.c\
		   treat_path.c\
		   init.c\
		   resolnew.c\
		   compat.c\
		   move_ant.c\
		   utils2.c\

INCFILES = lem_in.h
LIB = $(addprefix $(LIBDIR),$(LIBFILES))
SRC = $(addprefix $(SRCDIR),$(SRCFILES))
INC = $(addprefix $(INCDIR),$(INCFILES)) libft/includes/libft.h
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra -I includes -I libft/includes
QTY := $(shell echo ${SRCFILES} | wc -w)
CNT = 0
COLSET = 0
SIZE = 0
ASIZE = 0

all: lib $(NAME)

%.o: %.c $(INC)
	@$(eval CNT=$(shell echo "$(CNT) + 1" | bc))
	@$(eval COLSET=$(shell echo "$(CNT) * 255 / $(QTY)" | bc))
	@$(eval SIZE=$(shell echo "$(CNT) * 100 / $(QTY)" | bc))
	@$(eval ASIZE=$(shell echo "100 - $(SIZE)" | bc))
	@printf "[48;2;255;$(COLSET);0m%$(SIZE)s[0m%$(ASIZE)s $(NAME)             \r" "" "" $(SIZE)
	@gcc -c -o $@ $< $(FLAG)

lib: $(LIBDIR)
	@make -C $(LIBDIR)
	@printf "\n"

$(NAME): $(LIB) $(OBJ) $(INC)
	@printf "\nLinking $(NAME)\r"
	@gcc -o $@ $(OBJ) $(FLAG) $(LIB) 
	@printf "$(NAME) Linked     \n"

clean:
	@printf "cleaning $(NAME)\r"
	@rm -f $(OBJ)
	@make clean -C $(LIBDIR)
	@printf "$(NAME) Cleaned    \n"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB)

re: fclean all
