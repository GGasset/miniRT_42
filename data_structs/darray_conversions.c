/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:50:01 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/23 12:52:27 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/dynamic_array.h"
#include <stdio.h>

char	*dstr(t_darray *darr)
{
	char	*str;

	str = (char *) darr->darray;
	free(darr);
	return (str);
}

char	**dpstr(t_darray *darr)
{
	char	**pstr;

	pstr = (char **) darr->darray;
	free(darr);
	return (pstr);
}
