# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/05 12:24:50 by mtaquet      #+#   ##    ##    #+#        #
#    Updated: 2019/04/29 14:48:41 by mtaquet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = ../visu
LIBDIR = ../libft/
MLXDIR = minilibx/
SRCDIR = srcs/
INCDIR = includes/
LIBFILES = libft.a
MLXFILES = libmlx.a
SRCFILES = init.c\
		   input.c\
		   main.c\
		   event.c\
		   util.c\
		   other_utils.c\
		   image_init.c\
		   image.c\
		   image_manip.c\
		   manip_foreground.c\
		   draw.c\
		   room.c\

INCFILES = visual.h
LIB = $(addprefix $(LIBDIR),$(LIBFILES))
MLX = $(addprefix $(MLXDIR),$(MLXFILES))
SRC = $(addprefix $(SRCDIR),$(SRCFILES))
INC = $(addprefix $(INCDIR),$(INCFILES)) minilibx/mlx.h
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra -I includes -I ../libft/includes -I minilibx

all: lib mlx $(NAME)

%.o: %.c $(INC)
	gcc -c -o $@ $< $(FLAG)

lib:
	@make -C $(LIBDIR)

mlx:
	@make -C $(MLXDIR)

$(NAME): $(LIB) $(MLX) $(OBJ) $(INC)
	gcc -o $@ $(LIB) $(MLX) $(OBJ) $(FLAG) -framework OpenGL -framework AppKit


clean:
	rm -f $(OBJ)
	make clean -C $(LIBDIR)
	make clean -C minilibx


fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)

re: fclean all
