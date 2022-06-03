# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flee <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 19:20:13 by flee              #+#    #+#              #
#    Updated: 2022/01/03 19:20:14 by flee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Cub3d

SRCS= main.c get_file.c parse.c square_map.c game_loop.c game_img.c game_raycasting.c \
		game_display.c game_move.c parse_wall.c parse_map.c game_utils.c clean.c 

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}

OBJS_BONUS		=	${addprefix srcs/bonus/,${SRCS_BONUS:.c=.o}}

LD_FLAGS		=	-L libft -L mlx

MLX_FLAGS		=	-lm -lmlx -lXext -lX11 

HEAD			=	-I includes -I libft -I mlx 

CC				=	clang 

CFLAGS			=	-Wall -Werror -Wextra -O3 -g3

.c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					make -C libft
					make -C mlx
					${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} -lft ${MLX_FLAGS}

all				:	${NAME}


clean			:
					make clean -C libft
					make clean -C mlx
					@rm -rf ${OBJS} 

fclean			:	clean
					make fclean -C libft
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
