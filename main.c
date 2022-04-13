/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:53:29 by stissera          #+#    #+#             */
/*   Updated: 2022/04/13 19:09:36 by stissera         ###   ########.fr       */
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
	m.matrix = map_parse(argv[1], size);
	m.id = mlx_init();
	m.winx = 1204;
	m.winy = 768;
	m.win_id = mlx_new_window(m.id, m.winx, m.winy, "Fdf42 - By stisera");
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
//	int		*color;

	i = -1;
	while (++i < count)
	{
		def = ft_split(split[i], ',');

		matrix[i] = malloc(sizeof(t_matrix *) * 1);
		matrix[i]->y = y;
		matrix[i]->x = i;
		matrix[i]->z = ft_atoi(def[0]);
		if (def[1])
		{
			//	color = argb_to_i(def[1]);
// LE PRINCIPE EST BON EN REVANCHE IL PEUT Y AVOIR 0XFFFFFF ou 0xff....
			matrix[i]->a = (def[1][2] - 55) * 16 + (def[1][3] - 55);
			matrix[i]->r = (def[1][4] - 55) * 16 + (def[1][5] - 55);
			matrix[i]->g = (def[1][6] - 55) * 16 + (def[1][7] - 55);
			matrix[i]->b = (def[1][8] - 55) * 16 + (def[1][8] - 55);
		}
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
/* 
int	*argb_to_i(char *hex)
{
	int	*argb[4];
	// count size of argb - 2;
	int argb[0] = ((hex[2]-55)*16 + (hex[3]-55));
	int argb[1] = ((hex[4]-55)*16 + (hex[5]-55));
	int argb[2] = ((hex[6]-55)*16 + (hex[7]-55));
	int argb[3] = ((hex[8]-55)*16 + (hex[9]-55));
	return (argb);
}
 */
