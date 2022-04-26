/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:22:22 by stissera          #+#    #+#             */
/*   Updated: 2022/04/26 19:12:26 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	*map_test(char *file)
{
	int		fd;
	int		*size;

	size = malloc(sizeof(int) * 2);
	if (!size)
		exit(0);
	fd = open(file, O_RDONLY);
	if (fd < 1)
	{
		printf("Your file '%s' doesn't exist!", file);
		exit(0);
	}
	size[0] = 0;
	size[1] = 0;
	map_test_next(size, fd, file);
	return (size);
}

void	map_test_next(int *size, int fd, char *file)
{
	int		i;
	char	**split;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		size[1]++;
		split = ft_split(line, ' ');
		while (split[i])
			i++;
		if (size[0] != 0 && size[0] != i)
		{
			close(fd);
			printf("BAD PARSSING MAP on file: %s\n", file);
			exit(0);
		}
		size[0] = i;
		while (i > 0)
			free(split[i--]);
		free(split);
		free(line);
		line = get_next_line(fd);
	}
}
