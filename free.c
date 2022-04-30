/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:09:55 by stissera          #+#    #+#             */
/*   Updated: 2022/04/30 17:30:23 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	free_matrix(t_global *m)
{
	int	x;
	int	y;

	y = m->sizey;
	while (--y >= 0)
	{
		x = m->sizex;
		while (--x >= 0)
			free(m->m_sum[y][x]);
		free(m->m_sum[y]);
	}
	free(m->m_sum);
	m->m_sum = NULL;
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
	}
	free(m->matrix);
	free(m->line);
	mlx_destroy_image(m->id, m->img);
	mlx_destroy_window(m->id, m->win_id);
	exit(0);
}

void	free_info(char **citoa)
{
	int	i;

	i = 6;
	while (--i >= 0)
		free(citoa[i]);
	citoa = NULL;
}
