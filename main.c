/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:53:29 by stissera          #+#    #+#             */
/*   Updated: 2022/04/17 20:07:32 by stissera         ###   ########.fr       */
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
	m.winx = 1024;
	m.winy = 768;
	m.zoom = 1;
	m.matrix = map_parse(argv[1], size);
	m.line = malloc(sizeof(t_draw) * 1);
	m.id = mlx_init();
	m.win_id = mlx_new_window(m.id, m.winx, m.winy, "Fdf42 - By stisera");
	testmatrix(&m);
	testdot(&m);
	mlx_loop(m.id);
	free(size);
	return (0);
}

