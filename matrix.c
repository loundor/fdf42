/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:33:05 by stissera          #+#    #+#             */
/*   Updated: 2022/04/25 23:10:34 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	***map_parse(char *file, int *size)
{
	int			fd;
	char		*line;
	char		**split;
	t_matrix	***matrix;
	int			xy[2];

	fd = open(file, O_RDONLY);
	matrix = malloc(sizeof(t_matrix ***) * size[1]);
	xy[1] = -1;
	while (++xy[1] < size[1])
		matrix[xy[1]] = malloc(sizeof(t_matrix **) * size[0]);
	xy[0] = 0;
	xy[1] = -1;
	line = get_next_line(fd);
	while (++xy[1] < size[1])
	{
		split = ft_split(line, ' ');
		put_matrix_line(matrix[xy[1]], xy[1], size[0], split);
		free_split(split, size[0]);
		free(line);
		line = get_next_line(fd);
	}
	return (matrix);
}

void	put_matrix_line(t_matrix **matrix, int y, int count, char **split)
{
	int		i;
	char	**def;

	i = -1;
	while (++i < count)
	{
		def = ft_split(split[i], ',');
		matrix[i] = malloc(sizeof(t_matrix) * 1);
		matrix[i]->y = y;
		matrix[i]->x = i;
		matrix[i]->z = ft_atoi(def[0]);
		if (def[1] != NULL)
			convert_htoi(def[1] + 2, matrix[i]->color);
		 else
			color_by_z(matrix[i]->z, matrix[i]->color);
		free(def);
	}
}

int	ft_htod(char h)
{
	h = ft_toupper(h);
	if (h >= '0' && h <= '9')
		return (h - 48);
	if (h >= 'A' && h <= 'F')
		return (h - 55);
	return (-1);
}

void	convert_htoi(char *hex, unsigned char *color)
{
	int	count;
	int	rgba;
	int	i;

	count = -1;
	i = 3;
	while (++count < ft_strlen(hex))
	{
		rgba = 0;
		rgba += ft_htod(hex[count++]);
		rgba = rgba * 16 + ft_htod(hex[count]);
		color[i--] = rgba;
	}
}

void	color_by_z(int z, unsigned char *color)
{
	if (z == 0)
	{
		color[0] = 0;
		color[1] = 255;
		color[2] = 0;
		color[3] = 0;
	}
	else if (z > 150)
	{
		color[0] = 255;
		color[1] = 218;
		color[2] = 224;
		color[3] = 230;
	}
	else if (z > 60)
	{
		color[0] = 255;
		color[1] = 42;
		color[2] = 98;
		color[3] = 150;
	}
	else if (z > 20)
	{
		color[0] = 255;
		color[1] = 80;
		color[2] = 68;
		color[3] = 21;
	}
	else if (z > 0)
	{
		color[0] = 255;
		color[1] = 0;
		color[2] = 255;
		color[3] = 0;
	}
	else
	{
		color[0] = 255;
		color[1] = 110;
		color[2] = 26;
		color[3] = 11;
	}
}

void	free_split(char **split, int size)
{
	while (size >= 0)
		free(split[size--]);
	free(split);
}

t_matrix	***matrix_sum(t_global *m)
{
	t_matrix	***map;
	int			y;
	int			x;

	y = -1;
	m->errm = 0;
	map = malloc(sizeof(t_matrix ***) * m->sizey);
	while (++y < m->sizey)
	{
		x = -1;
		map[y] = malloc(sizeof(t_matrix **) * m->sizex);
		while (++x < m->sizex)
		{
			map[y][x] = malloc(sizeof(t_matrix *) * 1);
			map[y][x]->z = m->matrix[y][x]->z * m->zzoom * m->zoom;
			map[y][x]->x = m->matrix[y][x]->x * m->zoom
				* m->scale + (m->marginx / 2);
			map[y][x]->y = m->matrix[y][x]->y * m->zoom
				* m->scale + (m->marginy);
		}
	}
	y = -1;
	while (++y < m->sizey)
	{
		x = -1;
		while (++x < m->sizex)
		{
			x_rotate(&map[y][x]->y, &map[y][x]->z, m);
			y_rotate(&map[y][x]->x, &map[y][x]->z, m);
			z_rotate(&map[y][x]->x, &map[y][x]->y, m);
			if (x > 0 && m->errm > map[y][x]->x)
				m->errm = map[y][x]->x;
		}
	}
	return (map);
}

void	matrix_draw(t_global *m)
{
	int	x;
	int	y;

	y = -1;
	while (++y < m->sizey)
	{
		x = -1;
		while (++x < m->sizex)
		{
			if (x < m->sizex - 1)
			{
				m->line->x = (m->m_sum[y][x]->x
						+ -1 * m->errm + m->marginx) / 2;
				m->line->y = (m->m_sum[y][x]->y) / 2;
				m->line->x1 = (m->m_sum[y][x + 1]->x
						+ -1 * m->errm + m->marginx) / 2;
				m->line->y1 = (m->m_sum[y][x + 1]->y) / 2;
				m->line->color = m->matrix[y][x]->color;
				draw_line(m);
			}
			if (y < m->sizey - 1)
			{
				m->line->x = (m->m_sum[y][x]->x + -1
						* m->errm + m->marginx) / 2;
				m->line->y = (m->m_sum[y][x]->y) / 2;
				m->line->x1 = (m->m_sum[y + 1][x]->x
						+ -1 * m->errm + m->marginx) / 2;
				m->line->y1 = (m->m_sum[y + 1][x]->y) / 2;
				m->line->color = m->matrix[y][x]->color;
				draw_line(m);
			}
		}
	}
	free_matrix(m);
}

void	free_matrix(t_global *m)
{
	int	x;
	int	y;

	y = m->sizey;
	while (--y > 0)
	{
		x = m->sizex;
		while (--x > 0)
			free(m->m_sum[y][x]);
		free(m->m_sum[y]);
		y--;
	}
	free(m->m_sum);
}

void	free_all(t_global *m)
{
	int	x;
	int	y;

	y = m->sizey;
	while (--y >= 0)
	{
		x = m->sizex;
		while (--x >= 0)
			free(m->matrix[y][x]);
		free(m->matrix[y]);
		y--;
	}
	while (--y >= 0)
	{
		x = m->sizex;
		while (--x >= 0)
			free(m->matrix[y][x]);
		free(m->matrix[y]);
		y--;
	}
	free(m->matrix);
	mlx_destroy_image(m->id, m->img);
	mlx_destroy_image(m->id, m->info);
	mlx_destroy_window(m->id, m->win_id);
	//mlx_destroy_display(m->id);
}

int	refresh_all(t_global *m)
{
	if (m->lmouse == MOUSEL)
	{
		if (m->radx - (m->lmousey - m->mousey) * 0.002 != m->radx)
		{
			m->radx -= (m->lmousey - m->mousey) * 0.002;
			//m->radz -= (m->lmousex - m->mousex) * 0.002;
		}
		if (m->rady - (m->lmousex - m->mousex) * 0.002 != m->rady)
		{
			m->rady -= (m->lmousex - m->mousex) * 0.002;
			//m->radz -= (m->lmousey - m->mousey) * 0.002;
		}
		//mlx_mouse_get_pos(m->win_id, &m->lmousex, &m->lmousey);
		mlx_mouse_get_pos(m->id, m->win_id, &m->lmousex, &m->lmousey);
	}
	if (m->lmouse == MOUSER)
	{
		if (m->marginy - (m->lmousey - m->mousey) != m->marginy)
			m->marginy -= (m->lmousey - m->mousey) * 1.3;
		if (m->marginx - (m->lmousex - m->mousex) != m->marginx)
			m->marginx -= (m->lmousex - m->mousex) * 1.3;
		//mlx_mouse_get_pos(m->win_id, &m->lmousex, &m->lmousey);
		mlx_mouse_get_pos(m->id, m->win_id, &m->lmousex, &m->lmousey); 
	}
	mlx_clear_window(m->id, m->win_id);
	ft_memset(m->data, 0x00000000, m->size_img * m->winy);
	m->m_sum = matrix_sum(m);
	matrix_draw(m);
	mlx_put_image_to_window(m->id, m->win_id, m->img, 0, 0);
	info(m);
	return (0);
}
