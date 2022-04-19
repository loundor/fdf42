/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:18:30 by stissera          #+#    #+#             */
/*   Updated: 2022/04/19 23:19:17 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	mouse_hook(int mouse, int x, int y, t_global *m)
{
	(void)m;
	printf("mouse: %d x:%d - y:%d", mouse, x, y);
	return (0);
}

int	key_hook(int key, t_global *m)
{
	if (key == ESC)
		mlx_loop_end(m->id);
	if (key == LEFT)
		return (0);// MOVE LEFT
	if (key == RIGHT)
		return (0);// MOVE RIGHT
	if (key == UP)
		return (0);// MOVE UP
	if (key == DOWN)
		return (0);// MOVE DOWN
	if (key == ZOOMP)
		m->zoom += 1;
	if (key == ZOOMM)
		m->zoom -= 1;
	if (key == YP)
		m->rad += 0.01;// rotate y+
	if (key == YM)
		m->rad -= 0.01;// rotate y-
	if (key == XP)
		m->rad += 0.01;// rotate x+
	if (key == XM)
		m->rad -= 0.01;// rotate x-
	key_hook2(key, m);
//	refresh_all();
	return (0);
}

void	key_hook2(int key, t_global *m)
{
	(void)key;
	(void)m;
}
