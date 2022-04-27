/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:11:45 by stissera          #+#    #+#             */
/*   Updated: 2022/04/27 12:35:38 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

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
	free(line);
	return (matrix);
}

void	put_matrix_line(t_matrix **matrix, int y, int count, char **split)
{
	int		i;
	char	**def;

	i = -1;
	while (++i < count)
	{
		def = ft_split(split[i], ',');
		matrix[i] = malloc(sizeof(t_matrix) * 1);
		matrix[i]->y = y;
		matrix[i]->x = i;
		matrix[i]->z = ft_atoi(def[0]);
		if (def[1] != NULL)
			convert_htoi(def[1] + 2, matrix[i]->color);
		else
			color_by_z(matrix[i]->z, matrix[i]->color);
		if (def[1])
			free(def[1]);
		free(def[0]);
		free(def);
	}
}
