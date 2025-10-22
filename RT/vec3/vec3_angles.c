/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_angles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:11:40 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 17:11:41 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_data	vec_angle(t_vec3 a, t_vec3 b)
{
	t_data	out;

	a = norm(a);
	b = norm(b);
	out = dot(a, b) / (modulus(a) * modulus(b));
	if (out != out)
		return (0);
	if (out > 1)
		out = 1;
	if (out < -1)
		out = -1;
	out = acos(out);
	out *= 180 / 3.14159;
	return (out);
}

t_vec3	get_angles(t_vec3 a, t_vec3 b)
{
	t_vec3	out;
	t_vec3	tmp[2];

	a = norm(a);
	b = norm(b);
	tmp[0] = vec3(0, y(a), z(a));
	tmp[1] = vec3(0, y(b), z(b));
	out.vs[0] = vec_angle(tmp[0], tmp[1]);
	if (z(a) > z(b) || y(a) > y(b))
		out.vs[0] *= -1;
	tmp[0] = vec3(x(a), 0, z(a));
	tmp[1] = vec3(x(b), 0, z(b));
	out.vs[1] = vec_angle(tmp[0], tmp[1]);
	if (x(a) > x(b) || z(a) > z(b))
		out.vs[1] *= -1;
	tmp[0] = vec3(x(a), y(a), 0);
	tmp[1] = vec3(x(b), y(b), 0);
	out.vs[2] = vec_angle(tmp[0], tmp[1]);
	if (x(a) > x(b) || y(a) > y(b))
		out.vs[2] *= -1;
	return (out);
}
