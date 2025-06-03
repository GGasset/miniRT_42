/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:32:29 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/07 18:02:05 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free(void **pntr, int condition)
{
	if (!pntr)
		return (0);
	free((void *)((condition != 0) * (size_t)(*pntr)));
	*pntr = 0;
	return (condition);
}
