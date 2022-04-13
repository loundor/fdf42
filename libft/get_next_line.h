/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:25:32 by stissera          #+#    #+#             */
/*   Updated: 2022/04/13 14:51:40 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# define BUFFER_SIZE 2

char	*add_to_str(char *str, int fd);
char	*ft_get_line(char *str);
char	*ft_remove_send(size_t start, char *str);
char	*get_next_line(int fd);
#endif
