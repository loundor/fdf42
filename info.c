/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:07:24 by stissera          #+#    #+#             */
/*   Updated: 2022/04/30 17:34:33 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	info(t_global *m)
{
	char	*citoa[6];

	citoa[0] = ft_itoa(m->mousex);
	citoa[1] = ft_itoa(m->mousey);
	citoa[2] = ft_itoa(m->scale);
	citoa[3] = ft_itoa(m->zoom * 100);
	citoa[4] = ft_itoa(m->radx * 180 / M_PI);
	citoa[5] = ft_itoa(m->rady * 180 / M_PI);
	mlx_mouse_get_pos(m->id, m->win_id, &m->mousex, &m->mousey);
	mlx_string_put(m->id, m->win_id, 0, 50, 0xFFFFFF, "Mouse X:");
	mlx_string_put(m->id, m->win_id, 60, 50, 0xFFFFFF, citoa[0]);
	mlx_string_put(m->id, m->win_id, 100, 50, 0xFFFFFF, "Mouse Y:");
	mlx_string_put(m->id, m->win_id, 160, 50, 0xFFFFFF, citoa[1]);
	mlx_string_put(m->id, m->win_id, 0, 60, 0xFFFFFF, "Scale:");
	mlx_string_put(m->id, m->win_id, 60, 60, 0xFFFFFF, citoa[2]);
	mlx_string_put(m->id, m->win_id, 100, 60, 0xFFFFFF, "Zoom:");
	mlx_string_put(m->id, m->win_id, 160, 60, 0xFFFFFF, citoa[3]);
	mlx_string_put(m->id, m->win_id, 0, 70, 0xFFFFFF, "Deg X:");
	mlx_string_put(m->id, m->win_id, 60, 70, 0xFFFFFF, citoa[4]);
	mlx_string_put(m->id, m->win_id, 100, 70, 0xFFFFFF, "Deg Y:");
	mlx_string_put(m->id, m->win_id, 160, 70, 0xFFFFFF, citoa[5]);
	free_info(citoa);
	return (0);
}
