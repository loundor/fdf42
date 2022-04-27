NAME	= fdf
LIBFT	= libft.a
MLXGL	= libmlx.a
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
SRCS	=	main.c \
			free.c \
			info.c \
			parssing.c \
			utils.c \
			draw.c \
			color.c \
			matrix.c \
			hook.c \
			map.c \
			rotate.c
OBJS	= $(addprefix ./, ${SRCS:.c=.o})

HEADER	= -I./ -I./libft -I./minilibx_opengl_20191021
MLX		= -lmlx -framework OpenGL -framework AppKit
#UNIX	= -lbsd -lmlx -lXext -lX11
RM		= @rm -rf

.c.o	:
			@$(CC) $(FLAGS) -c $(HEADER) $< $ -o ${<:.c=.o}

all 	:	$(NAME)

$(NAME) :	$(LIBFT) $(MLXGL) $(OBJS)
			@echo "Compiling FDF. ⚙️"
			@$(CC) $(OBJS) $(LIBFT) $(MLXGL) $(MLX) -o $@
			@echo "Finish... 🕶"

$(LIBFT):
			@echo "Make of libft...🔥"
			@make -s -C ./libft
			@mv ./libft/libft.a ./

$(MLXGL):
			@echo "Make of minilibx OpenGL...🔥"
			@make -s -C ./minilibx_opengl_20191021
			@mv ./minilibx_opengl_20191021/libmlx.a ./

clean	:
			@echo "Cleaning object... 🗑"
			@$(RM) $(OBJS)
			@echo "Cleaning libft...🗑"
			@make -s -C ./libft clean
			@echo "Cleaning MinilibX OpenGL...🗑"
			@make -s -C ./minilibx_opengl_20191021 clean

fclean	:	clean
			@$(RM) $(NAME) $(LIBFT) $(MLXGL) 
			@make -C ./libft fclean
			@echo "Full clean finish... 🧹"

re		:	fclean all

.PHONY	:	all clean fclean re
