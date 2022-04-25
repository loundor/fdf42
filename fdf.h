/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:43:48 by stissera          #+#    #+#             */
/*   Updated: 2022/04/25 23:15:39 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
//# include "./mlx/mlx.h"
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "./libft/libft.h"
# include "./libft/get_next_line.h"
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
# define ZP 118 // v
# define ZM 98 // b
# define ZMP 121 // y
# define ZMM 104 // h
# define ANGLEP 117 // u
# define ANGLEM 106 // j
# define ENTER 65293

// KEYBOARD MLX MACOS DEFINE
/* # define UP 13 // w
# define DOWN 1 // s
# define LEFT 0 // a
# define RIGHT 2 // d
# define PLUS 69 // +
# define MINUS 78 // -
# define ESC 53
# define SPACE 49
# define ZOOMM 12 // q
# define ZOOMP 14 // e
# define XP 15 // r
# define XM 3 // f
# define YP 17 // t
# define YM 5 // g
# define ZP 9 // v
# define ZM 11 // b
# define ZMP 16 // y
# define ZMM 4 // h
# define ANGLEP 32 // u
# define ANGLEM 38 // j
# define ENTER 36 */

// MOUSE MLX UNIX DEFINE
# define MOUSEL 1
# define MOUSER 2
# define MOUSEM 3
# define MOUSEUP 4
# define MOUSEDOWN 5
# define MOUSEPREV 8
# define MOUSENEXT 9

typedef struct s_matrix
{
	int				x;
	int				y;
	int				z;
	int				z1;
	unsigned char	color[4];
}	t_matrix;

typedef struct s_draw
{
	int				x;
	int				y;
	int				x1;
	int				y1;
	int				px;
	int				py;
	int				dx;
	int				dy;
	int				dx1;
	int				dy1;
	int				xi;
	int				yi;
	unsigned char	*color;
}	t_draw;

typedef struct s_global
{
	void		*id;
	void		*win_id;
	void		*img;
	char		*data;
	int			bpp;
	int			endian;
	int			size_img;
	void		*info;
	int			winx;
	int			winy;
	t_matrix	***matrix;
	t_matrix	***m_sum;
	t_draw		*line;
	int			sizex;
	int			sizey;
	int			mousex;
	int			mousey;
	int			lmousex;
	int			lmousey;
	int			lmouse;
	int			start;
	float		zoom;
	float		radx;
	float		rady;
	float		radz;
	float		radiso;
	int			view;
	int			scale;
	int			marginx;
	int			marginy;
	int			errm;
	int			zzoom;
}	t_global;

int			*map_test(char *file);
t_matrix	***map_parse(char *file, int *size);
void		put_matrix_line(t_matrix **matrix, int y,
				int count, char **split);
void		free_split(char **split, int size);

t_matrix	***matrix_sum(t_global *m);
void		matrix_draw(t_global *m);
void		reset_param(t_global *m);
void		color_by_z(int z, unsigned char *color);
int			ft_htod(char h);
void		convert_htoi(char *hex, unsigned char *color);

// DRAW FUNCTION
void		draw_line(t_global *m);
void		draw_line_b(t_global *m);
void		draw_line_s(t_global *m);
void		free_matrix(t_global *m);

// ROTATION AND ADJUST
void		x_rotate(int *xy, int *z, t_global *m);
void		y_rotate(int *xy, int *z, t_global *m);
void		z_rotate(int *x, int *y, t_global *m);
void		adjust_z(int *x, int *y, int z, t_global *m);

// KEYBOARD AND MOUSE
int			key_hook(int key, t_global *m);
void		key_hook2(int key, t_global *m);
int			mouse_hook(int mouse, int x, int y, t_global *m);
int			mouse_press(int mouse, int x, int y, t_global *m);
int			mouse_release(int mouse, int x, int y, t_global *m);
int			refresh_all(t_global *m);

// DEBUG FUNCTION
int			info(t_global *m);
void		default_param(t_global *m);
void		free_all(t_global *m);
#endif
