# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 12:57:01 by mleitner          #+#    #+#              #
#    Updated: 2023/08/17 14:44:43 by rmocsai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= cub3D
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
					line.c\
					minimap_raycast.c \
					error_1.c \
					error_2.c \
					parsing_1.c \
					parsing_2.c \
					colors.c \
					checker_1.c \
					checker_2.c \
					checker_3.c \
					checker_4.c \
					utils_1.c \
					get_map.c

CLR_RM 			:= \033[0m
BOLD 			:= \033[1m
MAGENTA			:= \033[0;95m
CYAN 			:= \033[1;36m
RED		    	:= \033[1;31m

SRCS			:= $(addprefix ${SRCSDIR}, ${SRCSLIST})

OBJSDIR			:= ./obj/
OBJSLIST		:= ${SRCSLIST:.c=.o}
OBJS			:= $(addprefix ${OBJSDIR}, ${OBJSLIST})

HEADDIR			:= ./inc/

LIBFTDIR		:= ./libft/
LIBFT			:= ${LIBFTDIR}libft.a

LIBS			:= -L${LIBFTDIR} -lft -lmlx -lXext -lX11 -lm
INCS			:= -I${HEADDIR} -I${LIBFTDIR}

.PHONY:			all clean fclean re norm

all:			${NAME}

${NAME}:		${LIBFT} ${OBJSDIR} ${OBJS}
				@echo "$(CYAN)$(BOLD)Compilation is in progress...$(CLR_RM)"
				${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${LIBS} ${INCS}
				@echo "$(CYAN)$(BOLD)You can play with $(RED)cub3D$(CYAN) now!$(CLR_RM)"

${LIBFT}:
				make -C ${LIBFTDIR}

${OBJSDIR}%.o:	${SRCSDIR}%.c
				${CC} ${FLAGS} ${DEBUG} ${INCS} -c $< -o $@

${OBJSDIR}:
				mkdir -p ${OBJSDIR}

clean:
				${RM} -r ${OBJSDIR}
				make -C ${LIBFTDIR} clean

fclean:			clean
				${RM} ${NAME}
				make -C ${LIBFTDIR} fclean

re:				fclean all

make norm:
				norminette ${SRCSDIR} ${HEADDIR}
