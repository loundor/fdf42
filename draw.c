/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:32:31 by stissera          #+#    #+#             */
/*   Updated: 2022/04/22 01:30:29 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	draw_line(t_global *m)
{
	m->line->px = abs(m->line->x1 - m->line->x);
	m->line->py = abs(m->line->y1 - m->line->y);
	m->line->dx = 2 * m->line->px;
	m->line->dy = 2 * m->line->py;
	m->line->dx1 = m->line->px;
	m->line->dy1 = m->line->py;
	m->line->xi = 1;
	m->line->yi = 1;
	if (m->line->x > m->line->x1)
		m->line->xi = -1;
	if (m->line->y > m->line->y1)
		m->line->yi = -1;
	if (m->line->dx1 > m->line->dy1)
		draw_line_b(m);
	if (m->line->dx1 < m->line->dy1)
		draw_line_s(m);
}

void	draw_line_b(t_global *m)
{
	int	i;
/* 	char *pix; */

	i = 0;
	while (i <= m->line->dx1)
	{
		if (m->line->x > 0 && m->line->x <= m->winx
				&& m->line->y > 0 && m->line->y <= m->winy)
/* 		{
			printf("-%d-", (m->line->x + m->line->y) * (m->bpp/8));
			pix = m->data + ((m->line->x + (m->line->y * m->winx)) * (m->bpp/8));
			*(int *)pix = m->line->color;
		} */
		mlx_pixel_put(m->id, m->win_id, m->line->x, m->line->y, m->line->color);
		i++;
		m->line->x += m->line->xi;
		m->line->px -= m->line->dy;
		if (m->line->px < 0)
		{
			m->line->y += m->line->yi;
			m->line->px += m->line->dx;
		}
	}
}

void	draw_line_s(t_global *m)
{
	int	i;
/* char *pix; */

	i = 0;
	while (i <= m->line->dy1)
	{
/* 		if (m->line->x > 0 && m->line->x <= m->winx && m->line->y > 0 && m->line->y <= m->winy)
		{
			pix = m->data + ((m->line->x * (m->line->y * m->winx)) * (m->bpp/8));
			*(int *)pix = m->line->color;
		} */
			//*(int *)(m->data + ((m->line->x + m->line->y * m->winx) * m->bpp)) = m->line->color;
		mlx_pixel_put(m->id, m->win_id, m->line->x, m->line->y, m->line->color);
		i++;
		m->line->y += m->line->yi;
		m->line->py -= m->line->dx;
		if (m->line->py < 0)
		{
			m->line->x += m->line->xi;
			m->line->py += m->line->dy;
		}
	}
}
