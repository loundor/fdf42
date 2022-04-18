/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:43:48 by stissera          #+#    #+#             */
/*   Updated: 2022/04/18 22:59:16 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	testdot(t_global *m)
{
	int	y;
	int	x;

	y = 0;
	while (y < m->sizey)
	{
		x = 0;
		while (x < m->sizex)
		{
			if (x + 1 < m->sizex)
			{
			m->line->x = (m->matrix[y][x]->x * ((m->winx - 300) / m->sizex) + 150) * m->zoom;
			m->line->y = (m->matrix[y][x]->y * ((m->winy - 100) / m->sizey) + 50) * m->zoom;
			m->line->x1 = (m->matrix[y][x + 1]->x * ((m->winx - 300) / m->sizex) + 150) * m->zoom;
			m->line->y1 = (m->matrix[y][x + 1]->y * ((m->winy - 100) / m->sizey) + 50) * m->zoom - (x * 10);
			}
			if (m->matrix[y][x]->z)
			{
				if (m->matrix[y][x]->z == 1)
					m->line->color = 100100255;
				if (m->matrix[y][x]->z == 2)
					m->line->color = 255;
				if (m->matrix[y][x]->z == 3)
					m->line->color = 28128;
				if (m->matrix[y][x]->z == 4)
					m->line->color = 128255;
				if (m->matrix[y][x]->z > 5)
					m->line->color = 255128;
			}
			else
				m->line->color = 255255255;
			draw_line(m);
			if (y > 0)
			{
				m->line->x = (m->matrix[y][x]->x * ((m->winx - 300) / m->sizex) + 150) * m->zoom;
				m->line->y = (m->matrix[y][x]->y * ((m->winy - 100) / m->sizey) + 50) * m->zoom;
				m->line->x1 = (m->matrix[y - 1][x]->x * ((m->winx - 300) / m->sizex) + 150) * m->zoom - (x * 10);
				m->line->y1 = (m->matrix[y - 1][x]->y * ((m->winy - 100) / m->sizey) + 50) * m->zoom;
				draw_line(m);
			}
			x++;

		}
		y++;
	}

	// CROSS
	m->line->x = (m->matrix[0][0]->x * ((m->winx - 300) / m->sizex) + 150) * m->zoom;
	m->line->y = (m->matrix[0][0]->y * ((m->winy - 100) / m->sizey) + 50) * m->zoom;
	m->line->x1 = (m->matrix[m->sizey - 1][m->sizex - 1]->x * ((m->winx - 300) / m->sizex) + 150) * m->zoom;
	m->line->y1 = (m->matrix[m->sizey - 1][m->sizex - 1]->y * ((m->winy - 100) / m->sizey) + 50) * m->zoom;
	draw_line(m);

	m->line->x = (m->matrix[m->sizey - 1][0]->x * ((m->winx - 300) / m->sizex) + 150) * m->zoom;
	m->line->y = (m->matrix[m->sizey - 1][0]->y * ((m->winy - 100) / m->sizey) + 50) * m->zoom;
	m->line->x1 = (m->matrix[0][m->sizex - 1]->x * ((m->winx - 300) / m->sizex) + 150) * m->zoom;
	m->line->y1 = (m->matrix[0][m->sizex - 1]->y * ((m->winy - 100) / m->sizey) + 50) * m->zoom;
	draw_line(m);
	// END CROSS
}

void	testmatrix(t_global *m)
{
	int	x;
	int	y;
	int	h;

	x = -1;
	y = -1;
	while (++y < m->sizey)
	{
		while (++x < m->sizex)
		{
			printf("x%2d", m->matrix[y][x]->x * ((m->winx - 200) / m->sizex));
			printf("y%2d", m->matrix[y][x]->y * ((m->winy - 200) / m->sizey));
			printf("z%2d", m->matrix[y][x]->z * 1);
			printf("c%9s | ", m->matrix[y][x]->color);
			if (m->matrix[y][x]->z > 0)
				h = 255255;
			else
				h = 255;
			mlx_pixel_put(m->id, m->win_id,
				(m->matrix[y][x]->x * ((m->winx - 500) / m->sizex) + 250) * m->zoom,
				(m->matrix[y][x]->y * ((m->winy - 500) / m->sizey) + 250) * m->zoom,
				h);
		}
		printf("\n");
		x = -1;
	}
}
