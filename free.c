/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:09:55 by stissera          #+#    #+#             */
/*   Updated: 2022/04/27 12:38:59 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	free_matrix(t_global *m)
{
	int	x;
	int	y;

	y = m->sizey;
	while (--y > 0)
	{
		x = m->sizex;
		while (--x > 0)
			free(m->m_sum[y][x]);
		free(m->m_sum[y]);
		y--;
	}
	free(m->m_sum);
}

void	free_all(t_global *m)
{
	int	x;
	int	y;

	y = m->sizey;
	while (--y >= 0)
	{
		x = m->sizex;
		while (--x >= 0)
			free(m->matrix[y][x]);
		free(m->matrix[y]);
		y--;
	}
	while (--y >= 0)
	{
		x = m->sizex;
		while (--x >= 0)
			free(m->matrix[y][x]);
		free(m->matrix[y]);
		y--;
	}
	free(m->matrix);
	free(m->line);
	mlx_destroy_image(m->id, m->img);
	mlx_destroy_window(m->id, m->win_id);
	exit(0);
}
