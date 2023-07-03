# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 02:03:03 by tchoquet          #+#    #+#              #
#    Updated: 2023/07/02 19:53:41 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT				= .
SRCS_DIR			= ${ROOT}/sources
INCLUDES_DIR		= ${ROOT}/includes
BUILD_DIR			= ${ROOT}/build
DEPENDENCIES_DIR	= Libft MiniLibXWrapper 2DGraphics 3DGraphics

SRC			= ${wildcard ${SRCS_DIR}/*.c}
OBJ			= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}

CC						= gcc
CFLAGS					= -Wall -Wextra -Werror
memcheck: CFLAGS		+= -D MEMCHECK

INCLUDES				= $(foreach dir,${INCLUDES_DIR} ${DEPENDENCIES_DIR}, -I${dir})
LIBS					= 	Libft/libft.a						\
							MiniLibXWrapper/libwrapped_mlx.a	\
							2DGraphics/lib2D_Graphics.a			\
							3DGraphics/lib3D_Graphics.a
EXTERNAL_LIBS			= -framework OpenGL -framework AppKit
memcheck: EXTERNAL_LIBS	+= -l memory_leak_detector
memcheck: MEM			= memcheck

NAME		= ${ROOT}/fdf


.PHONY: all clean fclean re Libft MiniLibXWrapper 2DGraphics 3DGraphics dependencies norm memcheck


all: dependencies ${NAME}

${NAME}: ${OBJ}
	${CC} -o $@ $^ ${LIBS} ${EXTERNAL_LIBS}

${BUILD_DIR}/%.o: ${SRCS_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< ${INCLUDES}


clean:
	rm -rf ${BUILD_DIR}


fclean: clean
	make -C Libft fclean
	make -C MiniLibXWrapper fclean
	make -C 2DGraphics fclean
	make -C 3DGraphics fclean
	rm -rf ${NAME} ${EXPORT_INCLUDE}


re: fclean all

dependencies: Libft MiniLibXWrapper 2DGraphics 3DGraphics

Libft:
	make -C Libft ${MEM}

MiniLibXWrapper:
	make -C MiniLibXWrapper ${MEM}

2DGraphics:
	make -C 2DGraphics ${MEM}

3DGraphics:
	make -C 3DGraphics ${MEM}

norm:
	make -C Libft norm 
	make -C MiniLibXWrapper norm 
	make -C 2DGraphics norm 
	make -C 3DGraphics norm 
	norminette ${SRCS_DIR} ${INCLUDES_DIR}


memcheck: all


${BUILD_DIR}:
	mkdir -p $@
	