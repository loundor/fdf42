/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:43:48 by stissera          #+#    #+#             */
/*   Updated: 2022/04/16 13:01:57 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	testdot(t_global *m)
{
	int	x;
	int	y;
	//int	h;

	x = -1;
	y = -1;

	mlx_pixel_put(m->id, m->win_id, 40, 250, 255255);
	mlx_pixel_put(m->id, m->win_id, 800, 600, 255255);

	mlx_pixel_put(m->id, m->win_id, 39, 250, 255255);
	mlx_pixel_put(m->id, m->win_id, 801, 600, 255255);



	mlx_pixel_put(m->id, m->win_id, (798-40)/2+40, (598-250)/2+250, 255255);
	mlx_pixel_put(m->id, m->win_id, (800-40)/2+40, (600-250)/2+250, 255255);
	mlx_pixel_put(m->id, m->win_id, (802-40)/2+40, (602-250)/2+250, 255255);

	mlx_pixel_put(m->id, m->win_id, 38, 250, 255255);
	mlx_pixel_put(m->id, m->win_id, 802, 600, 255255);

	mlx_pixel_put(m->id, m->win_id, 41, 250, 255255);
	mlx_pixel_put(m->id, m->win_id, 803, 600, 255255);

	draw_line(m, 40, 250, 800, 600);

/* 	while (++y < m->sizey)
	{
		while (++x < m->sizex)
		{
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
	} */
}

void	testmatrix(t_global *m)
{
	int	x;
	int	y;

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
		}
		printf("\n");
		x = -1;
	}
}
