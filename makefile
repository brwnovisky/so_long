LIBFT = ./lib/libft/libft.a

LIBFTPATH = ./lib/libft/

NAME = so_long

SRC = ./src/so_long.c \
	  ./src/map_verify.c \
	  ./src/game_exec.c \

MLX_FLAGS = -lmlx -lXext -lX11
CC = gcc

CFLAG = -Wall -Werror -Wextra -g

INC = -I ./inc/

OBJS = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} 
		make -C $(LIBFTPATH)
		${CC}  ${CFLAG} ${OBJS} $(MLX_FLAGS) ${LIBFT} -o ${NAME}

.c.o:
		${CC} ${CFLAG} ${INC} -c $< -o ${<:.c=.o}

clean:
		make clean -C $(LIBFTPATH)
		rm -f ${OBJS}

fclean: clean
		make fclean -C $(LIBFTPATH)
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re