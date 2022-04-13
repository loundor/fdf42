NAME	= fdf
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
SRCS	= main.c
OBJS	= $(addprefix ./, ${SRCS:.c=.o})
HEADER	= 
MLX		= -Lmlx -lmlx -framework OpenGL -framework AppKit
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
