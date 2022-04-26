NAME	= fdf
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
SRCS	=	main.c \
			matrix.c \
			draw.c \
			hook.c \
			rotate.c \
			map.c \
			free.c \
			info.c \
			parssing.c \
			utils.c \
			color.c
OBJS	= $(addprefix ./, ${SRCS:.c=.o})
HEADER	= fdf.h
MLX		= -Lmlx -lmlx -framework OpenGL -framework AppKit
UNIX	= -lbsd -lmlx -lXext -lX11
RM		= rm -rf

.c.o	:
			$(CC) $(FLAGS) $(MLX) $< -o ${<:.c=.o}

all 	:	$(NAME)

$(NAME) :	$(OBJS)
			$(CC) $(MLX) -I./ $(OBJS) -o $@

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
