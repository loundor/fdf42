/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:43:48 by stissera          #+#    #+#             */
/*   Updated: 2022/04/19 23:31:01 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "./libft/libft.h"
# include "./libft/get_next_line.h"
# define BASE16 "0123456789abcfdef"
# define NAMEAUT "Projet fdf 42 Mulhouse"

// KEYBOARD MLX UNIX DEFINE
# define UP 119 // w
# define DOWN 115 // s
# define LEFT 97 // a
# define RIGHT 100 // d
# define PLUS 65 // +
# define MINUS 45 // -
# define ESC 65307
# define SPACE 32
# define ZOOMM 113 // q
# define ZOOMP 101 // e
# define XP 114 // r
# define XM 102 // f
# define YP 116 // t
# define YM 103 // g
# define ZP 121 // y
# define ZM 104 // h
# define ANGLEP 117 // u
# define ANGLEM 106 // j
# define ENTER 65293
// MOUSE MLX UNIX DEFINE
# define MOUSEL 1
# define MOUSEM 2
# define MOUSER 3
# define MOUSEUP 4
# define MOUSEDOWN 5
# define MOUSEPREV 8
# define MOUSENEXT 9

typedef struct s_matrix
{
	int					x;
	int					y;
	int					z;
	int					z1;
	char				color[11];
}	t_matrix;

// COORDINATE OF X,Y and X1, Y1 must be full!
typedef struct s_draw
{
	int	x;
	int	y;
	int	x1;
	int	y1;
	int	px;
	int	py;
	int	dx;
	int	dy;
	int	dx1;
	int	dy1;
	int	xi;
	int	yi;
	int	color;
}	t_draw;

typedef struct s_global
{
	void		*id;
	void		*win_id;
	void		*img;
	void		*info;
	int			winx;
	int			winy;
	t_matrix	***matrix;
	t_draw		*line;
	int			sizex;
	int			sizey;
	int			mousex;
	int			mousey;
	int			start;
	int			zoom;
	float		rad;
	float		radiso;
	int			view;
	int			scale;
	int			margin;
}	t_global;

int			*map_test(char *file);
t_matrix	***map_parse(char *file, int *size);
void		put_matrix_line(t_matrix **matrix, int y, int count, char **split);
void		free_split(char **split, int size);

// TO CODE
//int			*argb_to_i(char *hex);
char		*i_to_argb(int a, int r, int g, int b);
// int			*argb_to_i(char *hex);
t_matrix	*first_line_matrix(char **tab);
t_matrix	*line_to_matrix(char *line, t_matrix *matrix);

// DRAW FUNCTION
void		draw_line(t_global *m);
void		draw_line_b(t_global *m);
void		draw_line_s(t_global *m);

// ROTATION AND ADJUST
void		rotate(int *xy, int *z, t_global *m);
void		z_rotate(int *x, int *y, t_global *m);
void		adjust_z(int *x, int *y, int z, t_global *m);

// KEYBOARD AND MOUSE
int			key_hook(int key, t_global *m);
void		key_hook2(int key, t_global *m);
int			mouse_hook(int mouse, int x, int y, t_global *m);

// DEBUG FUNCTION
void		testmatrix(t_global *m);
void		testdot(t_global *m);
void		draw_line_G(t_global *m);
int			info(t_global *m);
void		default_param(t_global *m);

#endif
