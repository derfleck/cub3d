# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 12:57:01 by mleitner          #+#    #+#              #
#    Updated: 2023/08/18 18:02:54 by mleitner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= cub3D
BONUSNAME		:= cub3D_bonus
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
BONUSSRCSLIST	:= ${SRCSLIST:.c=_bonus.c}
BONUSSRCS		:= $(addprefix ${SRCSDIR}, ${BONUSSRCSLIST})

CLR_RM 			:= \033[0m
BOLD 			:= \033[1m
MAGENTA			:= \033[0;95m
CYAN 			:= \033[1;36m
RED		    	:= \033[1;31m

SRCS			:= $(addprefix ${SRCSDIR}, ${SRCSLIST})

OBJSDIR			:= ./obj/
OBJSLIST		:= ${SRCSLIST:.c=.o}
OBJS			:= $(addprefix ${OBJSDIR}, ${OBJSLIST})
BONUSOBJSLIST	:= ${BONUSSRCSLIST:.c=.o}
BONUSOBJS		:= $(addprefix ${OBJSDIR}, ${BONUSOBJSLIST})

HEADDIR			:= ./inc/

LIBFTDIR		:= ./libft/
LIBFT			:= ${LIBFTDIR}libft.a

MLXDIR			:= ./mlx_linux/
MLX				:= ${MLXDIR}libmlx.a

LIBS			:= -L${LIBFTDIR} -L${MLXDIR} -lft -lmlx -lXext -lX11 -lm
INCS			:= -I${HEADDIR} -I${LIBFTDIR} -I${MLXDIR}

.PHONY:			all clean fclean re norm bonus

all:			${NAME}

${NAME}:		${MLX} ${LIBFT} ${OBJSDIR} ${OBJS}
				@echo "$(CYAN)$(BOLD)Compilation is in progress...$(CLR_RM)"
				${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${LIBS} ${INCS}
				@echo "$(CYAN)$(BOLD)You can play with $(RED)cub3D$(CYAN) now!$(CLR_RM)"

${BONUSNAME}:	${MLX} ${LIBFT} ${OBJSDIR} ${BONUSOBJS}
				@echo "$(CYAN)$(BOLD)Compilation is in progress...$(CLR_RM)"
				${CC} ${FLAGS} ${DEBUG} ${BONUSOBJS} -o ${BONUSNAME} ${LIBS} ${INCS}
				@echo "$(CYAN)$(BOLD)You can play with $(RED)cub3D_bonus$(CYAN) now!$(CLR_RM)"

${LIBFT}:
				make -C ${LIBFTDIR}

${MLX}:
				make -C ${MLXDIR}

${OBJSDIR}%.o:	${SRCSDIR}%.c
				${CC} ${FLAGS} ${DEBUG} ${INCS} -c $< -o $@

${OBJSDIR}:
				mkdir -p ${OBJSDIR}

clean:
				${RM} -r ${OBJSDIR}
				make -C ${LIBFTDIR} clean
				make -C ${MLXDIR} clean

fclean:			clean
				${RM} ${NAME}
				${RM} ${BONUSNAME}
				make -C ${LIBFTDIR} fclean

re:				fclean all

bonus:			${BONUSNAME}

make norm:
				norminette ${SRCSDIR} ${HEADDIR}
