/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:18:30 by stissera          #+#    #+#             */
/*   Updated: 2022/04/22 14:32:25 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	mouse_release(int mouse, int x, int y, t_global *m)
{
//	printf("-Release %d --\n", mouse);
	if (mouse == MOUSEL)
			m->lmouse = 0;
	if (mouse == MOUSER)
			m->lmouse = 0;
	//refresh_all(m);
	return (0);
}

int	mouse_press(int mouse, int x, int y, t_global *m)
{
//	printf("-Press %d --\n", mouse);
	if (mouse == MOUSEL && m->lmouse == 0)
			m->lmouse = MOUSEL;
	if (mouse == MOUSER && m->lmouse == 0)
			m->lmouse = MOUSER;
	if (mouse == MOUSEUP && m->zoom < 2)
		m->zoom += 0.01;
	if (mouse == MOUSEDOWN && m->zoom > 0.01)
		m->zoom -= 0.01;
	refresh_all(m);
	return (0);
}

int	mouse_hook(int mouse, int x, int y, t_global *m)
{

	refresh_all(m);
	return (0);
}

int	key_hook(int key, t_global *m)
{
	if (key == ESC)
		exit(0);
		//mlx_loop_end(m->id);
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
		m->radx += 0.017;
	if (key == YM)
		m->radx -= 0.017;
	if (key == XP)
		m->rady += 0.017;
	if (key == XM)
		m->rady -= 0.017;
	key_hook2(key, m);
	refresh_all(m);
	return (0);
}

void	key_hook2(int key, t_global *m)
{
	if (key == ZP)
		m->radz += 0.017;
	if (key == ZM)
		m->radz -= 0.017;
	if (key == ZMP)
		m->zzoom -= 1;
	if (key == ZMM)
		m->zzoom += 1;
	if (key == SPACE)
		reset_param(m);
}
