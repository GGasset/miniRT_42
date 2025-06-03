/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_void.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:59:53 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/09 17:34:46 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sign(char c)
{
	return (c == '-' || c == '+');
}

static int	set_float(void *to_write, char *value, enum e_types t)
{
	float	f_val;
	double	d_val;
	int		error;

	error = 0;
	if (t == f32)
	{
		f_val = ft_atof_s(value, &error);
		if (!error)
			*(float *)to_write = f_val;
	}
	else if (t == f64)
	{
		d_val = ft_atod_s(value, &error);
		if (!error)
			*(double *)to_write = d_val;
	}
	else
		return (1);
	return (error);
}

static int	set_int(void *to_write, char *value)
{
	size_t	i;

	i = 0;
	while ((is_sign(value[i]) && i == 0) || ft_isdigit(value[i]))
		i++;
	if (value[i])
		return (1);
	*(int *)to_write = ft_atoi(value);
	return (0);
}

int	ft_set_void(void *to_write, char *value, enum e_types out_type)
{
	int		error;

	error = 0;
	if (!value || !to_write || out_type == other_type || out_type == nil)
		return (1);
	if (out_type == i32)
		error = set_int(to_write, value);
	else if (out_type == f32 || out_type == f64)
		error = set_float(to_write, value, out_type);
	else if (out_type == pntr)
		*(void **)to_write = value;
	else
		return (1);
	return (error);
}
