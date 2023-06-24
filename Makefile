# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 02:03:03 by tchoquet          #+#    #+#              #
#    Updated: 2023/06/24 19:00:47 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}/sources
INCLUDES_DIR 	= ${ROOT}/includes
BUILD_DIR		= ${ROOT}/build

SRC			= ${wildcard ${SRCS_DIR}/*.c}
OBJ			= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}
OBJ_DEBUG	= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=_debug.o}}

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror
alldebug: CFLAGS	= -g -D MEMCHEK
EXTERNAL_LIBS		= -l ft -l ftprintf -l wrapped_mlx -l 3D_Graphics -l 2D_Graphics -l memory_leak_detector -framework OpenGL -framework AppKit

NAME		= ${ROOT}/fdf
NAME_DEBUG	= ${ROOT}/Debug.out

vpath %.c ${ROOT} ${SRCS_DIR}

.PHONY: all clean fclean re debug alldebug cleandebug fcleandebug redebug


all: ${NAME}

${NAME}: ${OBJ}
	${CC} -o $@ $^ ${EXTERNAL_LIBS}

${BUILD_DIR}/%.o: %.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean all


debug: alldebug

alldebug: ${NAME_DEBUG}

${NAME_DEBUG}: ${OBJ_DEBUG}
	${CC} -o $@ $^ ${EXTERNAL_LIBS}

${BUILD_DIR}/%_debug.o: %.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}

cleandebug:
	rm -rf ${OBJ_DEBUG}

fcleandebug: cleandebug
	rm -rf ${NAME_DEBUG}

redebug: fcleandebug alldebug


#folders
${BUILD_DIR}:
	mkdir -p $@