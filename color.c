/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:46:34 by stissera          #+#    #+#             */
/*   Updated: 2022/04/27 15:22:15 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	color_by_z(int z, unsigned char *color)
{
	if (z == 0)
	{
		color[0] = 0;
		color[1] = 240;
		color[2] = 172;
		color[3] = 89;
	}
	else if (z > 150)
	{
		color[0] = 0;
		color[1] = 218;
		color[2] = 224;
		color[3] = 230;
	}
	else if (z > 60)
	{
		color[0] = 0;
		color[1] = 42;
		color[2] = 98;
		color[3] = 150;
	}
	else
		color_by_z_2(z, color);
}

void	color_by_z_2(int z, unsigned char *color)
{
	if (z > 20)
	{
		color[0] = 0;
		color[1] = 0;
		color[2] = 99;
		color[3] = 50;
	}
	else if (z > 0)
	{
		color[0] = 0;
		color[1] = 0;
		color[2] = 99;
		color[3] = 7;
	}
	else if (z < -100)
	{
		color[0] = 0;
		color[1] = 99;
		color[2] = 57;
		color[3] = 6;
	}
	else
		color_by_z_3(z, color);
}

void	color_by_z_3(int z, unsigned char *color)
{
	if (z < -50)
	{
		color[0] = 0;
		color[1] = 99;
		color[2] = 0;
		color[3] = 0;
	}
	else if (z < -20)
	{
		color[0] = 0;
		color[1] = 99;
		color[2] = 48;
		color[3] = 0;
	}
	else if (z < 0)
	{
		color[0] = 0;
		color[1] = 176;
		color[2] = 104;
		color[3] = 16;
	}
	else
		color_by_z_4(z, color);
}

void	color_by_z_4(int z, unsigned char *color)
{
	(void)z;
	color[0] = 0;
	color[1] = 0;
	color[2] = 32;
	color[3] = 59;
}
