/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:43:48 by stissera          #+#    #+#             */
/*   Updated: 2022/04/17 20:12:23 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	testdot(t_global *m)
{
	m->line->x = 20;
	m->line->y = 120;
	m->line->x1 = 490;
	m->line->y1 = 16;
	m->line->color = 255255;
	draw_line(m);

	m->line->x = 120;
	m->line->y = 240;
	m->line->x1 = 240;
	m->line->y1 = 0;
	m->line->color = 150100;
	draw_line(m);

	m->line->x = 980;
	m->line->y = 750;
	m->line->x1 = 200;
	m->line->y1 = 10;
	m->line->color = 255255255;
	draw_line(m);

	m->line->x = 500;
	m->line->y = 0;
	m->line->x1 = 505;
	m->line->y1 = 768;
	m->line->color = 180120213;
	draw_line(m);
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
