/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:07:24 by stissera          #+#    #+#             */
/*   Updated: 2022/04/26 20:39:03 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	info(t_global *m)
{
	//mlx_mouse_get_pos(m->win_id, &m->mousex, &m->mousey);
	mlx_mouse_get_pos(m->id, m->win_id, &m->mousex, &m->mousey);
	mlx_string_put(m->id, m->win_id, 0, 50, 0xFFFFFF, "Mouse X:");
	mlx_string_put(m->id, m->win_id, 60, 50, 0xFFFFFF, ft_itoa(m->mousex));
	mlx_string_put(m->id, m->win_id, 100, 50, 0xFFFFFF, "Mouse Y:");
	mlx_string_put(m->id, m->win_id, 160, 50, 0xFFFFFF, ft_itoa(m->mousey));
	mlx_string_put(m->id, m->win_id, 0, 60, 0xFFFFFF, "Scale:");
	mlx_string_put(m->id, m->win_id, 60, 60, 0xFFFFFF, ft_itoa(m->scale));
	mlx_string_put(m->id, m->win_id, 100, 60, 0xFFFFFF, "Zoom:");
	mlx_string_put(m->id, m->win_id, 160, 60, 0xFFFFFF,
		ft_itoa(m->zoom * 100));
	mlx_string_put(m->id, m->win_id, 0, 70, 0xFFFFFF, "Deg X:");
	mlx_string_put(m->id, m->win_id, 60, 70, 0xFFFFFF,
		ft_itoa(m->radx * 180 / M_PI));
	mlx_string_put(m->id, m->win_id, 100, 70, 0xFFFFFF, "Deg Y:");
	mlx_string_put(m->id, m->win_id, 160, 70, 0xFFFFFF,
		ft_itoa(m->rady * 180 / M_PI));
	return (0);
}
