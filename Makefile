# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 02:03:03 by tchoquet          #+#    #+#              #
#    Updated: 2023/07/02 18:52:45 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}/sources
INCLUDES_DIR	= ${ROOT}/includes
BUILD_DIR		= ${ROOT}/build

SRC			= ${wildcard ${SRCS_DIR}/*.c}
OBJ			= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror
memcheck: CFLAGS 	+= -D MEMCHECK
DEPENDENCIES		= -I Libft -I MiniLibXWrapper -I 2DGraphics -I 3DGraphics
LIBS				= 	Libft/libft.a						\
						MiniLibXWrapper/libwrapped_mlx.a	\
						2DGraphics/lib2D_Graphics.a			\
						3DGraphics/lib3D_Graphics.a
memcheck: MEM		= memcheck

NAME		= ${ROOT}/fdf


.PHONY: all clean fclean re norm memcheck


all: ${NAME}

${NAME}: ${LIBS} ${OBJ}
	ar rc $@ ${OBJ}

${BUILD_DIR}/%.o: ${SRCS_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR} ${DEPENDENCIES}


clean:
	rm -rf ${BUILD_DIR}


fclean: clean
	make -C Libft fclean
	make -C MiniLibXWrapper fclean
	make -C 2DGraphics fclean
	make -C 3DGraphics fclean
	rm -rf ${NAME} ${EXPORT_INCLUDE}


re: fclean all


norm:
	make -C Libft norm 
	make -C MiniLibXWrapper norm 
	make -C 2DGraphics norm 
	make -C 3DGraphics norm 
	norminette ${SRCS_DIR} ${INCLUDES_DIR}


memcheck: all


${BUILD_DIR}:
	mkdir -p $@


Libft/libft.a:
	make -C Libft ${MEM}
MiniLibXWrapper/libwrapped_mlx.a:
	make -C MiniLibXWrapper ${MEM}
2DGraphics/lib2D_Graphics.a:
	make -C 2DGraphics ${MEM}
3DGraphics/lib3D_Graphics.a:
	make -C 3DGraphics ${MEM}