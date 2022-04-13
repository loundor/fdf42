/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:43:48 by stissera          #+#    #+#             */
/*   Updated: 2022/04/13 19:03:45 by stissera         ###   ########.fr       */
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

typedef struct s_matrix
{
	int					x;
	int					y;
	int					z;
	int					a;
	int					r;
	int					g;
	int					b;
}	t_matrix;

typedef struct s_global
{
	void		*id;
	void		*win_id;
	int			winx;
	int			winy;
	t_matrix	***matrix;
	int			mousex;
	int			mousey;
	int			start;
	float		zoom;
	int			view;
	float		decalx;
	float		decaly;
}	t_global;



int			*map_test(char *file);
t_matrix	***map_parse(char *file, int *size);
void		put_matrix_line(t_matrix **matrix, int y, int count, char **split);
void		free_split(char **split, int size);

// TO CODE
//int			*argb_to_i(char *hex);
char		*i_to_argb(int a, int r, int g, int b);
t_matrix	*first_line_matrix(char **tab);
t_matrix	*line_to_matrix(char *line, t_matrix *matrix);

void		draw_line(t_global *global);

#endif