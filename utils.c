/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:08:15 by stissera          #+#    #+#             */
/*   Updated: 2022/04/26 15:12:58 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	ft_htod(char h)
{
	h = ft_toupper(h);
	if (h >= '0' && h <= '9')
		return (h - 48);
	if (h >= 'A' && h <= 'F')
		return (h - 55);
	return (-1);
}

void	convert_htoi(char *hex, unsigned char *color)
{
	int	count;
	int	rgba;
	int	i;

	count = -1;
	i = 3;
	while (++count < ft_strlen(hex))
	{
		rgba = 0;
		rgba += ft_htod(hex[count++]);
		rgba = rgba * 16 + ft_htod(hex[count]);
		color[i--] = rgba;
	}
}

void	free_split(char **split, int size)
{
	while (size >= 0)
		free(split[size--]);
	free(split);
}

int	refresh_all(t_global *m)
{
	if (m->lmouse == MOUSEL)
	{
		if (m->radx - (m->lmousey - m->mousey) * 0.002 != m->radx)
			m->radx -= (m->lmousey - m->mousey) * 0.002;
		if (m->rady - (m->lmousex - m->mousex) * 0.002 != m->rady)
			m->rady -= (m->lmousex - m->mousex) * 0.002;
		mlx_mouse_get_pos(m->win_id, &m->lmousex, &m->lmousey);
		//mlx_mouse_get_pos(m->id, m->win_id, &m->lmousex, &m->lmousey);
	}
	if (m->lmouse == MOUSER)
	{
		if (m->marginy - (m->lmousey - m->mousey) != m->marginy)
			m->marginy -= (m->lmousey - m->mousey) * 1.3;
		if (m->marginx - (m->lmousex - m->mousex) != m->marginx)
			m->marginx -= (m->lmousex - m->mousex) * 1.3;
		mlx_mouse_get_pos(m->win_id, &m->lmousex, &m->lmousey);
		//mlx_mouse_get_pos(m->id, m->win_id, &m->lmousex, &m->lmousey); 
	}
	mlx_clear_window(m->id, m->win_id);
	ft_memset(m->data, 0x00000000, m->size_img * m->winy);
	m->m_sum = matrix_sum(m);
	matrix_draw(m);
	mlx_put_image_to_window(m->id, m->win_id, m->img, 0, 0);
	info(m);
	return (0);
}
