/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:33:05 by stissera          #+#    #+#             */
/*   Updated: 2022/04/22 14:40:24 by stissera         ###   ########.fr       */
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
	int		colori;

	i = -1;
	while (++i < count)
	{
		def = ft_split(split[i], ',');
		matrix[i] = malloc(sizeof(t_matrix) * 1);
		matrix[i]->y = y;
		matrix[i]->x = i;
		matrix[i]->z = ft_atoi(def[0]);
		colori = -1;
		if (def[1])
			matrix[i]->color = (int)def[1];
		else
			matrix[i]->color = 0x00;
		free(def);
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
				m->line->x = (m->m_sum[y][x]->x + -1 * m->errm + m->marginx) / 2;
				m->line->y = (m->m_sum[y][x]->y) / 2;
				m->line->x1 = (m->m_sum[y][x + 1]->x + -1 * m->errm + m->marginx) / 2;
				m->line->y1 = (m->m_sum[y][x + 1]->y) / 2;
				if (!m->matrix[y][x]->color)
				{
					if (m->matrix[y][x]->z == 0 && m->matrix[y][x + 1]->z == 0)
						m->line->color = 0xFF;
					else
					{
						if (m->matrix[y][x]->z < 0)
							m->line->color = 0xFFFF00;
						else
							m->line->color = 0xFF00;
					}
				}
				else
					m->line->color = m->matrix[y][x]->color;
				draw_line(m);
			}
			if (y < m->sizey - 1)
			{
				m->line->x = (m->m_sum[y][x]->x + -1 * m->errm + m->marginx) / 2;
				m->line->y = (m->m_sum[y][x]->y) / 2;
				m->line->x1 = (m->m_sum[y + 1][x]->x + -1 * m->errm + m->marginx) / 2;
				m->line->y1 = (m->m_sum[y + 1][x]->y) / 2;
				if (!m->matrix[y][x]->color)
				{
					if (m->matrix[y][x]->z == 0 && m->matrix[y + 1][x]->z == 0)
						m->line->color = 0xFF00;
					else
					{
						if (m->matrix[y][x]->z < 0)
							m->line->color = 0xFF;
						else
							m->line->color = 0xFF00;
					}
				}
				else
					m->line->color = m->matrix[y][x]->color;
				draw_line(m);
			}
		}
	}
	free_matrix(m);
}

int	select_color(int z)
{
	if (z == 0)
		return (255255);
	else if (z == 1)
		return (255255);
	else if (z == 2)
		return (255);
	else
		return (128234100);
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
		mlx_mouse_get_pos(m->win_id, &m->lmousex, &m->lmousey);
		//mlx_mouse_get_pos(m->id, m->win_id, &m->lmousex, &m->lmousey);
		if (m->radx - (m->lmousey - m->mousey) * 0.002 != m->radx)
		{
			m->radx -= (m->lmousey - m->mousey) * 0.002;
			m->radz -= (m->lmousey - m->mousey) * 0.002;
		}
		if (m->rady - (m->lmousex - m->mousex) * 0.002 != m->rady)
		{
			m->rady -= (m->lmousex - m->mousex) * 0.002;
			//m->radz += (m->lmousey - m->mousey) * 0.002;
		}
	}
	if (m->lmouse == MOUSER)
	{
		mlx_mouse_get_pos(m->win_id, &m->lmousex, &m->lmousey);
		//mlx_mouse_get_pos(m->id, m->win_id, &m->lmousex, &m->lmousey);
		if (m->marginy - (m->lmousey - m->mousey) * 2 != m->marginy)
			m->marginy += (m->lmousey - m->mousey) * 2;
		if (m->marginx - (m->lmousex - m->mousex) * 2 != m->marginx)
			m->marginx += (m->lmousex - m->mousex) * 2;
	}

	mlx_clear_window(m->id, m->win_id);
	//mlx_destroy_image(m->id, m->img);
	ft_memset(m->data, 0x00000000, m->size_img * m->winy);
	//m->img = mlx_new_image(m->id, m->winx, m->winy);
	
	//m->data = mlx_get_data_addr(m->img, &m->bpp,
	//		&m->size_img, &m->endian);
	m->m_sum = matrix_sum(m);
	matrix_draw(m);
	mlx_put_image_to_window(m->id, m->win_id, m->img, 0, 0);
	info(m);
	return (0);
}
