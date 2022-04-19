/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:45:47 by stissera          #+#    #+#             */
/*   Updated: 2022/04/19 20:21:34 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	rotate(int *xy, int *z, t_global *m)
{
	*xy = *xy * cos(m->rad) + *z * sin(m->rad);
	*z = -(*xy) * sin(m->rad) + *z * cos(m->rad);
}

void	z_rotate(int *x, int *y, t_global *m)
{
	*x = *x * cos(m->rad) - *y * sin(m->rad);
	*y = (*x) * sin(m->rad) + *y * cos(m->rad);
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
