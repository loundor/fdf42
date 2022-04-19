/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:53:29 by stissera          #+#    #+#             */
/*   Updated: 2022/04/19 23:30:03 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

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
	default_param(&m);
	m.matrix = map_parse(argv[1], size);
	free(size);
	m.line = malloc(sizeof(t_draw) * 1);
//	testmatrix(&m);
	testdot(&m);
	//mlx_hook(m.win_id, DestroyNotify, StructureNotifyMask, exit_hook, &m);
	mlx_mouse_hook(m.win_id, mouse_hook, &m);
	mlx_key_hook(m.win_id, key_hook, &m);
	mlx_loop_hook(m.id, info, &m);
	mlx_loop(m.id);
//	free_all(&m);
	return (0);
}

void	default_param(t_global *m)
{
	m->id = mlx_init();
	m->winx = 1280;
	m->winy = 1024;
	m->margin = 200;
	m->scale = sqrt((pow(m->winx - m->margin, 2) + pow(m->winy, 2))) / m->sizex;
	m->rad = M_PI / 6;
	m->radiso = M_PI / 6;
	m->view = 1;
	m->zoom = 1;
	m->win_id = mlx_new_window(m->id, m->winx, m->winy, NAMEAUT);
	m->img = mlx_new_image(m->id, m->winx, m->winy);
	m->info = mlx_new_image(m->id, 200, 600);
}

int	info(t_global *m)
{
	char	*mx;
	char	*my;

	mlx_destroy_image(m->id, m->info);
	m->info = mlx_new_image(m->id, 200, 600);
	mlx_mouse_get_pos(m->id, m->win_id, &m->mousex, &m->mousey);
	mx = ft_itoa(m->mousex);
	my = ft_itoa(m->mousey);
	mlx_put_image_to_window(m->id, m->win_id, m->info, 980, 150);
	mlx_string_put(m->id, m->win_id, 1000, 200, 255255, mx);
	mlx_string_put(m->id, m->win_id, 1000, 220, 255, my);
	mlx_string_put(m->id, m->win_id, 1000, 240, 255, ft_itoa(m->scale));
	mlx_string_put(m->id, m->win_id, 1000, 260, 255,
		ft_itoa(m->rad * 180 / M_PI));
	mlx_string_put(m->id, m->win_id, 1000, 280, 255,
		ft_itoa(m->radiso * 180 / M_PI));
	mlx_string_put(m->id, m->win_id, 1000, 300, 255, ft_itoa(m->zoom));
	free(mx);
	free(my);
	return (0);
}
