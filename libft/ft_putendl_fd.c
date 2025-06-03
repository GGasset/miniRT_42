/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:07:22 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/18 16:04:33 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	s_len;
	char	endl;

	s_len = ft_strlen(s);
	endl = '\n';
	write(fd, s, s_len);
	write(fd, &endl, 1);
}
