/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:06:42 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/10/23 12:24:16 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/dynamic_array.h"

void	free_darray(t_darray *darray, int type)
{
	if (type == 1)
		free(darray->darray);
	else if (type == 2)
		ft_free_splitted(darray->darray);
	free(darray);
	darray = NULL;
}

t_darray	*alloc_darray(size_t len, size_t size)
{
	t_darray	*ret_darray;

	ret_darray = (t_darray *)ft_calloc(1, sizeof(t_darray));
	if (!ret_darray)
		return (NULL);
	ret_darray->darray = ft_calloc(len, sizeof(size));
	if (!ret_darray->darray)
		return (free(ret_darray), NULL);
	ret_darray->len = len;
	ret_darray->size = size;
	ret_darray->full_idx = 0;
	return (ret_darray);
}

int	resize_darray(t_darray **darray)
{
	size_t			i;
	void			*resz_darray;
	unsigned char	*str_darray;
	unsigned char	*str_resz_darray;

	i = 0;
	str_darray = (unsigned char *)(*darray)->darray;
	resz_darray = ft_calloc((2 * (*darray)->len), (*darray)->size);
	if (!resz_darray)
		return (0);
	str_resz_darray = (unsigned char *)resz_darray;
	while (i < (*darray)->len * (*darray)->size)
	{
		str_resz_darray[i] = str_darray[i];
		i++;
	}
	(*darray)->len *= 2;
	free((*darray)->darray);
	(*darray)->darray = resz_darray;
	return (1);
}

unsigned char	*r_darray(t_darray *darray, int idx)
{
	unsigned char	*str_darr;
	int				full_idx;
	size_t			bytes_size;

	full_idx = (int)darray->full_idx;
	if (!full_idx)
		return (darray->darray);
	if (-idx > full_idx || idx > full_idx - 1)
		return (NULL);
	if (idx >= 0)
		bytes_size = idx * darray->size;
	else
		bytes_size = (size_t)(full_idx + idx + 1) * darray->size;
	str_darr = &((unsigned char *)darray->darray)[bytes_size];
	return (str_darr);
}

int	append_darray(t_darray **darray, void *element)
{
	char	*str_darray;
	char	*str_element;
	size_t	i;

	i = 0;
	if ((*darray)->full_idx == (*darray)->len)
	{
		if (!resize_darray(darray))
			return (free_darray(*darray, 1), 0);
	}
	str_darray = (char *)r_darray(*darray, -1);
	str_element = (char *)element;
	while (i < (*darray)->size)
	{
		str_darray[i] = str_element[i];
		i++;
	}
	(*darray)->full_idx++;
	return (1);
}
