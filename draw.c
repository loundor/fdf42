/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:32:31 by stissera          #+#    #+#             */
/*   Updated: 2022/04/26 15:13:09 by stissera         ###   ########.fr       */
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

	i = 0;
	while (i <= m->line->dx1)
	{
		if (m->line->x > 0 && m->line->x <= m->winx
			&& m->line->y > 0 && m->line->y <= m->winy)
		{
			m->data[((m->line->y * m->size_img)) + m->line->x
				* (m->bpp / 8)] = m->line->color[1];
			m->data[((m->line->y * m->size_img)) + m->line->x
				* (m->bpp / 8) + 1] = m->line->color[2];
			m->data[((m->line->y * m->size_img)) + m->line->x
				* (m->bpp / 8) + 2] = m->line->color[3];
			m->data[((m->line->y * m->size_img)) + m->line->x
				* (m->bpp / 8) + 3] = m->line->color[0];
		}
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

	i = 0;
	while (i <= m->line->dy1)
	{
		if (m->line->x > 0 && m->line->x <= m->winx
			&& m->line->y > 0 && m->line->y <= m->winy)
		{
			m->data[((m->line->y * m->size_img)) + m->line->x
				* (m->bpp / 8)] = m->line->color[1];
			m->data[((m->line->y * m->size_img)) + m->line->x
				* (m->bpp / 8) + 1] = m->line->color[2];
			m->data[((m->line->y * m->size_img)) + m->line->x
				* (m->bpp / 8) + 2] = m->line->color[3];
			m->data[((m->line->y * m->size_img)) + m->line->x
				* (m->bpp / 8) + 3] = m->line->color[0];
		}
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
