# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 14:51:37 by mleitner          #+#    #+#              #
#    Updated: 2023/08/11 17:53:23 by mleitner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= cub3d
CC				:= cc
RM		    	:= rm -f
FLAGS			:= -Wall -Wextra -Werror
DEBUG			:= -g

SRCSDIR			:= ./src/
SRCSLIST		:= main.c\
					minimap.c\
					raycast.c\
					draw.c\
					move.c\
					draw_utils.c\
					textures.c\
					hooks.c\
					line.c
SRCS			:= $(addprefix ${SRCSDIR}, ${SRCSLIST})

OBJSDIR			:= ./obj/
OBJSLIST		:= ${SRCSLIST:.c=.o}
OBJS			:= $(addprefix ${OBJSDIR}, ${OBJSLIST})

LIBFTDIR		:= ./libft/
LIBFT			:= ${LIBFTDIR}libft.a

MLXDIR			:= ./mlx_linux/
MLX				:= ${MLXDIR}libmlx.a

LIBS			:= -L${LIBFTDIR} -L${MLXDIR} -lft -lmlx -lXext -lX11 -lm
INCS			:= -I${HEADDIR} -I${LIBFTDIR} -I${MLXDIR}

${NAME}:		${MLX} ${LIBFT} ${OBJSDIR} ${OBJS}
				${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${LIBS} ${INCS}

${LIBFT}:
				make -C ${LIBFTDIR}

${MLX}:
				make -C ${MLXDIR}

${OBJSDIR}%.o:	${SRCSDIR}%.c
				${CC} ${FLAGS} ${DEBUG} ${INCS} -c $< -o $@

${OBJSDIR}:
				mkdir -p ${OBJSDIR}

.PHONY:			all clean fclean re

all:			${NAME}

clean:
				${RM} -r ${OBJSDIR}
				make -C ${LIBFTDIR} clean
				make -C ${MLXDIR} clean

fclean:			clean
				${RM} ${NAME}
				make -C ${LIBFTDIR} fclean

re:				fclean all
