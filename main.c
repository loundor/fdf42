/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:53:29 by stissera          #+#    #+#             */
/*   Updated: 2022/04/16 13:04:30 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	*map_test(char *file)
{
	int		fd;
	int		*size;
	int		i;
	char	*line;
	char	**split;

	size = malloc(sizeof(int) * 2);
	if (!size)
		exit(0);
	fd = open(file, O_RDONLY);
	if (fd < 1)
	{
		printf("Your file '%s' doesn't exist!", file);
		exit(0);
	}
	line = get_next_line(fd);
	size[0] = 0;
	size[1] = 0;
	while (line)
	{
		size[1]++;
		i = 0;
		split = ft_split(line, ' ');
		while (split[i])
			i++;
		free(line);
		if (size[0] != 0 && size[0] != i)
		{
			close(fd);
			printf("BAD PARSSING MAP on file: %s\n", file);
			exit(0);
		}
		size[0] = i;
		line = get_next_line(fd);
	}
	return (size);
}

int	main(int argc, char **argv)
{
	t_global	m;
	int			*size;

	if (argc < 2)
	{
		printf("No arguments!");
		exit (0);
	}
	size = map_test(argv[1]);
	m.sizex = size[0];
	m.sizey = size[1];
	m.winx = 1204;
	m.winy = 768;
	m.zoom = 1;
	m.matrix = map_parse(argv[1], size);
	m.id = mlx_init();
//	testmatrix(&m);
	m.win_id = mlx_new_window(m.id, m.winx, m.winy, "Fdf42 - By stisera");
	testdot(&m);
	mlx_loop(m.id);
	free(size);
	return (0);
}

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
		colori = 0;
		if (def[1])
		{
			while (def[1][colori])
			{
				matrix[i]->color[colori] = def[1][colori];
				colori++;
			}
		}
		while (colori <= 10)
			matrix[i]->color[colori++] = '\0';
		free(def);
	}
}

void	free_split(char **split, int size)
{
	while (size >= 0)
	{
		free(split[size--]);
	}
	free(split);
}

void		draw_line(t_global *m, int x, int y, int x1, int y1)
{
	float	xd;
	float	yd;
	float	p;

	p = 0;
	mlx_pixel_put(m->id, m->win_id, x, y, 255);
	mlx_pixel_put(m->id, m->win_id, x1, y1, 255);
	while (x < x1 || y < y1)
	{
		//p += xd - (x1 - x);
		xd = 2 * (y1 - y);
		yd = xd - (2 * (x1 - x));
		p += xd - (x1 - x);
//			printf("x:%d, y:%d - x1:%d y1:%d\nxd: %d, yd:%d, p:%d\n ------- \n", x, y, x1, y1, xd, yd, p);
		if (p + .5 < 0)
		{
			write(1, "x\n", 2);
			x++;
			p += xd;
		}
		else
		{
			write(1, "y\n", 2);
			y++;
			p += yd;
		}
		mlx_pixel_put(m->id, m->win_id, x, y, 255);
	}

}
