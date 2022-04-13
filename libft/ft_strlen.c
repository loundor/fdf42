/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 10:49:04 by stissera          #+#    #+#             */
/*   Updated: 2022/04/13 15:12:43 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;
	size_t	i;

	if (!s)
		return (0);
	len = 0;
	i = 0;
	while (s[i])
	{
		len++;
		i++;
	}
	return (len);
}
