/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:53:29 by stissera          #+#    #+#             */
/*   Updated: 2022/04/26 18:49:44 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	main(int argc, char **argv)
{
	t_global	m;
	int			*size;

	if (argc != 2)
	{
		printf("No arguments or to few arguments!");
		exit (0);
	}
	size = map_test(argv[1]);
	m.sizex = size[0];
	m.sizey = size[1];
	default_param(&m);
	m.matrix = map_parse(argv[1], size);
	free(size);
	m.line = malloc(sizeof(t_draw) * 1);
	m.m_sum = matrix_sum(&m);
	matrix_draw(&m);
	hook_config(&m);
	mlx_put_image_to_window(m.id, m.win_id, m.img, 0, 0);
	mlx_loop(m.id);
	return (0);
}

void	hook_config(t_global *m)
{
	mlx_mouse_hook(m->win_id, mouse_hook, m);
	mlx_key_hook(m->win_id, key_hook, m);
	mlx_hook(m->win_id, 4, 1 << 2, mouse_press, m);
	mlx_hook(m->win_id, 5, 1 << 3, mouse_release, m);
	mlx_hook(m->win_id, 17, 0, exit_prg, m);
	mlx_loop_hook(m->id, refresh_all, m);
}

void	default_param(t_global *m)
{
	m->id = mlx_init();
	m->winx = 1280;
	m->winy = 1024;
	m->marginx = 200;
	m->marginy = 100;
	m->scale = sqrt((pow(m->winx, 2)
				+ pow(m->winy, 2))) / m->sizex;
	m->radx = M_PI / 6;
	m->rady = M_PI / 6;
	m->radz = M_PI / 6;
	m->radiso = M_PI / 6;
	m->lmouse = 0;
	m->lmousex = 0;
	m->lmousey = 0;
	m->view = 1;
	m->zoom = 1;
	m->zzoom = m->scale / -10 + -1;
	m->errm = 0;
	m->win_id = mlx_new_window(m->id, m->winx, m->winy, NAMEAUT);
	m->img = mlx_new_image(m->id, m->winx, m->winy);
	m->data = mlx_get_data_addr(m->img, &m->bpp,
			&m->size_img, &m->endian);
}

void	reset_param(t_global *m)
{
	m->marginx = 200;
	m->marginy = 100;
	m->scale = sqrt((pow(m->winx - m->marginx, 2)
				+ pow(m->winy, 2))) / m->sizex;
	m->radx = M_PI / 6;
	m->rady = M_PI / 6;
	m->radz = M_PI / 6;
	m->radiso = M_PI / 6;
	m->view = 1;
	m->zoom = 1;
	m->zzoom = m->scale / -10 + -1;
	m->errm = 0;
}
