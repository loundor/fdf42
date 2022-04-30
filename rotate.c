/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:45:47 by stissera          #+#    #+#             */
/*   Updated: 2022/04/30 21:44:25 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	x_rotate(int *xy, int *z, t_global *m)
{
	*xy = *xy * cos(m->radx) + *z * sin(m->radx);
	*z = -(*xy) * sin(m->radx) + *z * cos(m->radx);
}

void	y_rotate(int *xy, int *z, t_global *m)
{
	*xy = *xy * cos(m->rady) + *z * sin(m->rady);
	*z = -(*xy) * sin(m->rady) + *z * cos(m->rady);
}

void	z_rotate(int *x, int *y, t_global *m)
{
	*x = *x * cos(m->radz) - *y * sin(m->radz);
	*y = (*x) * sin(m->radz) + *y * cos(m->radz);
}

void	adjust_z(int *x, int *y, int z, t_global *m)
{
	int	xb;
	int	yb;

	xb = *x;
	yb = *y;
	*x = (xb - yb) * cos(m->radiso);
	*y = (xb + yb) * sin(m->radiso) - z;
}
