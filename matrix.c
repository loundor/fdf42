/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:33:05 by stissera          #+#    #+#             */
/*   Updated: 2022/04/20 13:33:35 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	***map_parse(char *file, int *size)
{
	int			fd;
	char		*line;
	char		**split;
	t_matrix	***matrix;
	int			xy[2];

	fd = open(file, O_RDONLY);
	matrix = malloc(sizeof(t_matrix ***) * size[1]);
	xy[1] = -1;
	while (++xy[1] < size[1])
		matrix[xy[1]] = malloc(sizeof(t_matrix **) * size[0]);
	xy[0] = 0;
	xy[1] = -1;
	line = get_next_line(fd);
	while (++xy[1] < size[1])
	{
		split = ft_split(line, ' ');
		put_matrix_line(matrix[xy[1]], xy[1], size[0], split);
		free_split(split, size[0]);
		free(line);
		line = get_next_line(fd);
	}
	return (matrix);
}

void	put_matrix_line(t_matrix **matrix, int y, int count, char **split)
{
	int		i;
	char	**def;
	int		colori;

	i = -1;
	while (++i < count)
	{
		def = ft_split(split[i], ',');
		matrix[i] = malloc(sizeof(t_matrix) * 1);
		matrix[i]->y = y;
		matrix[i]->x = i;
		matrix[i]->z = ft_atoi(def[0]);
		colori = -1;
		if (def[1])
		{
		//	matrix[i]->color = hextoi(def[1]);
			while (def[1][++colori])
				matrix[i]->color[colori] = def[1][colori];
		}
		while (colori <= 10)
			matrix[i]->color[colori++] = '\0';
		free(def);
	}
}

void	free_split(char **split, int size)
{
	while (size >= 0)
		free(split[size--]);
	free(split);
}

t_matrix	***matrix_sum(t_global *m)
{
	t_matrix	***map;
	int			y;
	int			x;

	y = -1;
	m->errm = 0;
	map = malloc(sizeof(t_matrix ***) * m->sizey);
	while (++y < m->sizey)
	{
		x = -1;
		map[y] = malloc(sizeof(t_matrix **) * m->sizex);
		while (++x < m->sizex)
		{
			map[y][x] = malloc(sizeof(t_matrix *) * 1);
			map[y][x]->z = m->matrix[y][x]->z * m->zzoom * m->zoom;
			map[y][x]->x = m->matrix[y][x]->x * m->zoom
				* m->scale + (m->marginx / 2);
			map[y][x]->y = m->matrix[y][x]->y * m->zoom
				* m->scale + (m->marginy);
		}
	}
	y = -1;
	while (++y < m->sizey)
	{
		x = -1;
		while (++x < m->sizex)
		{
			x_rotate(&map[y][x]->y, &map[y][x]->z, m);
			y_rotate(&map[y][x]->x, &map[y][x]->z, m);
			z_rotate(&map[y][x]->x, &map[y][x]->y, m);
			if (x > 0 && m->errm > map[y][x]->x)
				m->errm = map[y][x]->x;
		}
	}
	return (map);
}

void		matrix_draw(t_global *m)
{
	int	x;
	int	y;

	y = -1;
	while (++y < m->sizey)
	{
		x = -1;
		while (++x < m->sizex)
		{
			if (x < m->sizex - 1)
			{
				m->line->x = m->m_sum[y][x]->x + -1 * m->errm;
				m->line->y = m->m_sum[y][x]->y;
				m->line->x1 = m->m_sum[y][x + 1]->x + -1 * m->errm;
				m->line->y1 = m->m_sum[y][x + 1]->y;
				draw_line(m);
			}
			if (y < m->sizey - 1)
			{
				m->line->x = m->m_sum[y][x]->x + -1 * m->errm;
				m->line->y = m->m_sum[y][x]->y;
				m->line->x1 = m->m_sum[y + 1][x]->x + -1 * m->errm;
				m->line->y1 = m->m_sum[y + 1][x]->y;
				draw_line(m);
			}
		}
	}
}
