/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:33:25 by alvmoral          #+#    #+#             */
/*   Updated: 2025/06/03 00:04:29 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/RT_headers/camera.h"
#include "../Headers/RT_headers/vec3.h"
#include "../libft/libft.h"
#include <stdio.h>

int	get_index(char *id)
{
	if (!ft_strcmp(id, "A"))
		return (0);
	if (!ft_strcmp(id, "C"))
		return (1);
	if (!ft_strcmp(id, "L"))
		return (2);
	if (!ft_strcmp(id, "sp"))
		return (3);
	if (!ft_strcmp(id, "cy"))
		return (4);
	if (!ft_strcmp(id, "pl"))
		return (5);
	return (-1);
}

const char	*get_type_info(char *type)
{
	static const char	*type_info[] = {
		"rf:0-1,vi:0-255",
		"vf:i-i,vf:-1-1,ri:0-180",
		"vf:i-i,rf:0-1,vi:0-255",
		"vf:i-i,rf:0-1,vi:0-255",
		"vf:i-i,vf:-1-1,vi:0-255",
		"vf:i-i,vf:-1-1,rf:i,rf:i,vi:0-255"};
	return (type_info[get_index(type)]);
}

int	get_next_field(char **info_struct, char *field)
{
	static int	i = 0;
	
	if (info_struct[i] == NULL)
	{
		i = 0;
		ft_bzero(field, 8);
		return (0);
	}
	else
	{
		ft_strlcpy(field, info_struct[i], 8);
		i++;
		return (1);
	}
}

t_data	get_scalar(char *value)
{
	return (ft_atod(value));
}

t_vec3	*get_vector(char *value)
{
	char	**dim;
	t_vec3	*vec;

	dim = ft_split(value, ',');
	if (dim == NULL)
		return (NULL);

	vec = alloc_vec3(ft_atod(dim[0]), ft_atod(dim[1]), ft_atod(dim[2]));
	ft_free((void **) dim, 1);
	return (vec);
}

int	main(int argc, char **argv)
{
	char		field[8];
	const char	*infoA = get_type_info("A");
	char		**info_struct  = ft_split(infoA, ',');
	
	argv++;

	while (get_next_field(info_struct, field))	
	{
		// Aqui viene la logica para llenar
		//las estructuras que despues van a llenar las estructuras
	}
	ft_free((void **) info_struct, 1);
}
