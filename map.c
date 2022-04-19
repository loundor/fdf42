/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:22:22 by stissera          #+#    #+#             */
/*   Updated: 2022/04/19 23:22:38 by stissera         ###   ########.fr       */
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
