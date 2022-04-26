/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:07:24 by stissera          #+#    #+#             */
/*   Updated: 2022/04/26 15:07:43 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	info(t_global *m)
{
	mlx_destroy_image(m->id, m->info);
	m->info = mlx_new_image(m->id, 200, 600);
	mlx_mouse_get_pos(m->win_id, &m->mousex, &m->mousey); // OSX
	//mlx_mouse_get_pos(m->id, m->win_id, &m->mousex, &m->mousey); // UNIX
	mlx_put_image_to_window(m->id, m->win_id, m->info, 980, 150);
	mlx_string_put(m->id, m->win_id, 1000, 200, 255255, ft_itoa(m->mousex));
	mlx_string_put(m->id, m->win_id, 1000, 220, 255, ft_itoa(m->mousey));
	mlx_string_put(m->id, m->win_id, 1000, 240, 255, ft_itoa(m->scale));
	mlx_string_put(m->id, m->win_id, 1000, 260, 255,
		ft_itoa(m->radx * 180 / M_PI));
	mlx_string_put(m->id, m->win_id, 1000, 280, 255,
		ft_itoa(m->rady * 180 / M_PI));
	mlx_string_put(m->id, m->win_id, 1000, 300, 255, ft_itoa(m->zoom * 100));
	mlx_string_put(m->id, m->win_id, 1000, 320, 255, ft_itoa(m->lmouse));
	mlx_string_put(m->id, m->win_id, 1000, 330, 255, ft_itoa(m->lmousex));
	mlx_string_put(m->id, m->win_id, 1000, 340, 255, ft_itoa(m->lmousex));
	return (0);
}
