/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:43:48 by stissera          #+#    #+#             */
/*   Updated: 2022/04/20 13:39:56 by stissera         ###   ########.fr       */
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
		m->matrix[y][x]->y *= m->scale/2;
		m->matrix[y][x]->x *= m->scale/2;
		m->matrix[y][x]->z *= m->scale/2;
		x_rotate(&m->matrix[y][x]->y, &m->matrix[y][x]->z, m);
		y_rotate(&m->matrix[y][x]->x, &m->matrix[y][x]->z, m);
		z_rotate(&m->matrix[y][x]->x, &m->matrix[y][x]->y, m);
//		adjust_z(&m->matrix[y][x]->x, &m->matrix[y][x]->y, m->matrix[y][x]->z, m);
		while (x < m->sizex)
		{
			if (x + 1 < m->sizex)
			{
		m->matrix[y][x+1]->y *= m->scale/2;
		m->matrix[y][x+1]->x *= m->scale/2;
		m->matrix[y][x+1]->z *= m->scale/2;
				if (m->matrix[y][x]->z > 0 || m->matrix[y][x+1]->z > 0)
					m->line->color = 255255255;
				else
					m->line->color = 255;
				x_rotate(&m->matrix[y][x+1]->y, &m->matrix[y][x+1]->z, m);
				y_rotate(&m->matrix[y][x+1]->x, &m->matrix[y][x+1]->z, m);
				z_rotate(&m->matrix[y][x+1]->x, &m->matrix[y][x+1]->y, m);
//				adjust_z(&m->matrix[y][x+1]->x, &m->matrix[y][x+1]->y, m->matrix[y][x+1]->z, m);
				m->line->x = m->matrix[y][x]->x + ((m->scale * m->sizex / 2) - (m->marginx / 2));
				m->line->y = m->matrix[y][x]->y;
				m->line->x1 = m->matrix[y][x + 1]->x + ((m->scale * m->sizex / 2) - (m->marginx / 2));
				m->line->y1 = m->matrix[y][x + 1]->y;
			}
			draw_line(m);
			if (y > 0)
			{
				m->line->x = m->matrix[y][x]->x + ((m->scale * m->sizex / 2) - (m->marginx / 2));
				m->line->y = m->matrix[y][x]->y;
				m->line->x1 = m->matrix[y - 1][x]->x + ((m->scale * m->sizex / 2) - (m->marginx / 2));
				m->line->y1 = m->matrix[y - 1][x]->y;
				draw_line(m);
			}
			x++;
		}
		y++;
	}
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
			printf("y%2d", m->matrix[y][x]->y);
			printf("x%2d | ", m->matrix[y][x]->x);
			//printf("z%2d", m->matrix[y][x]->z * 1);
			//printf("c%4s | ", m->matrix[y][x]->color);
			if (m->matrix[y][x]->z > 0)
				h = 255255;
			else
				h = 255;
			mlx_pixel_put(m->id, m->win_id,
				m->matrix[y][x]->x, m->matrix[y][x]->y,
				h);
		}
		printf("\n");
		x = -1;
	}
}
