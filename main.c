/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:53:29 by stissera          #+#    #+#             */
/*   Updated: 2022/04/21 21:12:38 by stissera         ###   ########.fr       */
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
	//mlx_hook(m.win_id, DestroyNotify, StructureNotifyMask, exit_hook, &m);
	m.m_sum = matrix_sum(&m);
	matrix_draw(&m);
	mlx_mouse_hook(m.win_id, mouse_hook, &m);
	mlx_key_hook(m.win_id, key_hook, &m);
	//mlx_hook(m.win_id, 4, 1L << 2, mouse_press, &m);
	mlx_hook(m.win_id, 5, 1L << 3, mouse_release, &m);
	mlx_loop_hook(m.id, info, &m);
	mlx_loop(m.id);
	free_all(&m);
	return (0);
}

void	default_param(t_global *m)
{
	m->id = mlx_init();
	m->winx = 1280;
	m->winy = 1024;
	m->marginx = 200;
	m->marginy = 100;
	m->scale = sqrt((pow(m->winx - m->marginx, 2)
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
	m->zzoom = -1;
	m->errm = 0;
	m->win_id = mlx_new_window(m->id, m->winx, m->winy, NAMEAUT);
	m->img = mlx_new_image(m->id, m->winx, m->winy);
	m->info = mlx_new_image(m->id, 200, 600);
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
	m->zzoom = -50;
	m->errm = 0;
}

int	info(t_global *m)
{
	static int	x;
	static int	y;

	mlx_destroy_image(m->id, m->info);
	m->info = mlx_new_image(m->id, 200, 600);
	mlx_mouse_get_pos(m->win_id, &m->mousex, &m->mousey);
	mlx_put_image_to_window(m->id, m->win_id, m->info, 980, 150);
	mlx_string_put(m->id, m->win_id, 1000, 200, 255255, ft_itoa(m->mousex));
	mlx_string_put(m->id, m->win_id, 1000, 220, 255, ft_itoa(m->mousey));
	mlx_string_put(m->id, m->win_id, 1000, 240, 255, ft_itoa(m->scale));
	mlx_string_put(m->id, m->win_id, 1000, 260, 255,
		ft_itoa(m->radx * 180 / M_PI));
	mlx_string_put(m->id, m->win_id, 1000, 280, 255,
		ft_itoa(m->rady * 180 / M_PI));
	mlx_string_put(m->id, m->win_id, 1000, 300, 255, ft_itoa(m->zoom * 100));
	mlx_string_put(m->id, m->win_id, 1000, 320, 255, ft_itoa(m->lmouse));
	mlx_string_put(m->id, m->win_id, 1000, 330, 255, ft_itoa(m->lmousex));
	mlx_string_put(m->id, m->win_id, 1000, 340, 255, ft_itoa(m->lmousex));
	if (m->lmouse == 1)
	{
		if (m->radx - (m->lmousey - m->mousey) * 0.0001 != m->radx)
			m->radx += (m->lmousey - m->mousey) * 0.0001;
		if (m->rady - (m->lmousex - m->mousex) * 0.0001 != m->rady)
			m->rady += (m->lmousex - m->mousex) * 0.0001;
		x = m->radx;
		y = m->rady;
		mlx_mouse_get_pos(m->win_id, &m->lmousex, &m->lmousey);
	}
	return (0);
}
