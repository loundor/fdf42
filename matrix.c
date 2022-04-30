/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:33:05 by stissera          #+#    #+#             */
/*   Updated: 2022/04/30 09:57:04 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			if (!map)
				exit(0);
			map[y][x]->z = m->matrix[y][x]->z * m->zzoom * m->zoom;
			map[y][x]->x = m->matrix[y][x]->x * m->zoom
				* m->scale + (m->marginx / 2);
			map[y][x]->y = m->matrix[y][x]->y * m->zoom
				* m->scale + (m->marginy);
		}
	}
	matrix_sum_next(m, map);
	return (map);
}

void	matrix_sum_next(t_global *m, t_matrix ***map)
{
	int	y;
	int	x;

	y = -1;
	x = -1;
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
			matrix_draw_x(x, y, m);
			matrix_draw_y(x, y, m);
		}
	}
	free_matrix(m);
}

void	matrix_draw_x(int x, int y, t_global *m)
{
	if (x < m->sizex - 1)
	{
		m->line->x = (m->m_sum[y][x]->x
				+ -1 * m->errm + m->marginx) / 2;
		m->line->y = (m->m_sum[y][x]->y) / 2;
		m->line->x1 = (m->m_sum[y][x + 1]->x
				+ -1 * m->errm + m->marginx) / 2;
		m->line->y1 = (m->m_sum[y][x + 1]->y) / 2;
		if (m->matrix[y][x]->z < m->matrix[y][x + 1]->z)
			m->line->color = m->matrix[y][x + 1]->color;
		else
			m->line->color = m->matrix[y][x]->color;
		draw_line(m);
	}
}

void	matrix_draw_y(int x, int y, t_global *m)
{
	if (y < m->sizey - 1)
	{
		m->line->x = (m->m_sum[y][x]->x
				+ -1 * m->errm + m->marginx) / 2;
		m->line->y = (m->m_sum[y][x]->y) / 2;
		m->line->x1 = (m->m_sum[y + 1][x]->x
				+ -1 * m->errm + m->marginx) / 2;
		m->line->y1 = (m->m_sum[y + 1][x]->y) / 2;
		if (m->matrix[y + 1][x]->z > m->matrix[y][x]->z)
			m->line->color = m->matrix[y + 1][x]->color;
		else
			m->line->color = m->matrix[y][x]->color;
		draw_line(m);
	}
}
