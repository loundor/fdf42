/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:18:30 by stissera          #+#    #+#             */
/*   Updated: 2022/04/20 13:32:49 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	mouse_hook(int mouse, int x, int y, t_global *m)
{
	(void)m;
	printf("mouse: %d x:%d - y:%d", mouse, x, y);
	if (mouse == MOUSEUP && m->zoom < 128)
		m->zoom += 1;
	if (mouse == MOUSEDOWN && m->zoom > -128)
		m->zoom -= 1;

	return (0);
}

int	key_hook(int key, t_global *m)
{
	if (key == ESC)
		mlx_loop_end(m->id);
	if (key == LEFT)
		m->marginx -= 10;
	if (key == RIGHT)
		m->marginx += 10;
	if (key == UP)
		m->marginy -= 10;
	if (key == DOWN)
		m->marginy += 10;
	if (key == ZOOMP)
		m->zoom += 0.1;
	if (key == ZOOMM)
		m->zoom -= 0.1;
	if (key == YP)
		m->radx += 0.017;// rotate y+
	if (key == YM)
		m->radx -= 0.017;// rotate y-
	if (key == XP)
		m->rady += 0.017;// rotate x+
	if (key == XM)
		m->rady -= 0.017;// rotate x-
	key_hook2(key, m);
	mlx_clear_window(m->id, m->win_id);
	m->m_sum = matrix_sum(m); // write the good value in secondary matrix
	matrix_draw(m);
//	refresh_all();
	return (0);
}

void	key_hook2(int key, t_global *m)
{
	if (key == ZP)
		m->radz += 0.017;// rotate z+
	if (key == ZM)
		m->radz -= 0.017;// rotate z-
	if (key == ZMP)
		m->zzoom += 1;
	if (key == ZMM)
		m->zzoom -= 1;
	if (key == SPACE)
		reset_param(m);
}
