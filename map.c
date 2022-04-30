/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:22:22 by stissera          #+#    #+#             */
/*   Updated: 2022/04/30 10:08:27 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	*map_test(char *file)
{
	int		fd;
	int		*size;

	fd = open(file, O_RDONLY);
	if (fd < 1)
	{
		write(1, "Your file doesn't exist!\n", 26);
		exit(0);
	}
	size = malloc(sizeof(int) * 2);
	if (!size)
		exit(0);
	size[0] = 0;
	size[1] = 0;
	map_test_next(size, fd);
	return (size);
}

void	map_test_next(int *size, int fd)
{
	int		i;
	char	**split;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		size[1]++;
		split = ft_split(line, ' ');
		while (split[i])
			i++;
		if (size[0] != 0 && size[0] != i)
		{
			close(fd);
			write(1, "BAD PARSSING MAP on file.\n", 27);
			exit(0);
		}
		size[0] = i;
		while (--i >= 0)
			free(split[i]);
		free(split);
		free(line);
		line = get_next_line(fd);
	}
}
