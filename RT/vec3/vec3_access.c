/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:11:12 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 17:11:32 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_data	x(t_vec3 vec)
{
	return (vec.vs[0]);
}

t_data	y(t_vec3 vec)
{
	return (vec.vs[1]);
}

t_data	z(t_vec3 vec)
{
	return (vec.vs[2]);
}

void	print_vec3(t_vec3 vec)
{
	printf("(%lf, %lf, %lf)\n", x(vec), y(vec), z(vec));
}
