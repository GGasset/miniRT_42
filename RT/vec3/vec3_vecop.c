/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_vecop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:10:31 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 17:11:06 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_data	dot(t_vec3 v1, t_vec3 v2)
{
	return ((x(v1) * x(v2)) + (y(v1) * y(v2)) + (z(v1) * z(v2)));
}

t_vec3	norm(t_vec3 v)
{
	double	module;

	module = modulus(v);
	if (!module)
		return (v);
	return (vec_sdiv(v, module));
}

t_data	modulus(t_vec3 vec)
{
	return (sqrt(x(vec) * x(vec) + y(vec) * y(vec) + z(vec) * z(vec)));
}

t_vec3	n_unitary(t_vec3 a, t_vec3 b)
{
	t_vec3	out;

	out.vs[0] = y(a) * z(b) - y(b) * z(a);
	out.vs[1] = x(b) * z(a) - x(a) * z(b);
	out.vs[2] = x(a) * y(b) - x(b) * y(a);
	return (out);
}

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_data	tt;

	tt = vec_angle(a, b);
	return (vec_smul(n_unitary(a, b), modulus(a) * modulus(b) * sin(tt)));
}
