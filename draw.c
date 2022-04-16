/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:32:31 by stissera          #+#    #+#             */
/*   Updated: 2022/04/16 15:35:41 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_line(t_global *m, int x, int y, int x1, int y1)
{
	int px;
	int	py;
	int	dx;
	int dy;
	int dx1;
	int dy1;
	int i;
	int xi;
	int yi;

	px = abs(x1 - x);
	py = abs(y1 - y);
	dx = 2 * px;
	dy = 2 * py;
	dx1 = px;
	dy1 = py;
	i = 0;
	xi = 1;
	yi = 1;
	if (x > x1)
		xi = -1;
	if (y > y1)
		yi = -1;
	if (dx1 > dy1)
	{
		while (i <= dx1)
		{
			mlx_pixel_put(m->id, m->win_id, x, y, 255255);
			i++;
			x += xi;
			px -= dy;
			if (px < 0)
			{
				y += yi;
				px += dx;
			}
		}
	}
	if (dx1 < dy1)
	{
		while (i <= dy1)
		{
			mlx_pixel_put(m->id, m->win_id, x, y, 255);
			i++;
			y += yi;
			py -= dx;
			if (py < 0)
			{
				x += xi;
				py += dy;
			}
		}
	}
}
