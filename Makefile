# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/05 12:24:50 by mtaquet      #+#   ##    ##    #+#        #
#    Updated: 2019/05/02 17:35:08 by lperron     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = lem-in
LIBDIR = libft/
CHECKDIR = checker/
VISUDIR = visualisateur/
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

all: lib $(NAME) checku visuu

%.o: %.c $(INC)
	gcc -c -o $@ $< $(FLAG)

$(LIB): $(LIBDIR)
	make -C $(LIBDIR)

lib: $(LIBDIR)
	make -C $(LIBDIR)

checku: $(CHECKDIR)
	make -C $(CHECKDIR)

visuu: $(VISUDIR)
	make -C $(VISUDIR)

$(NAME): $(LIB) $(OBJ) $(INC) 
	gcc -o $@ $(OBJ) $(FLAG) $(LIB) 

clean:
	rm -f $(OBJ)
	make clean -C $(CHECKDIR)
	make clean -C $(VISUDIR)
	make clean -C $(LIBDIR)

fclean: clean
	rm -f $(NAME)
	rm -f check
	rm -f visu
	rm -f $(LIB)

re: fclean all
