/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:09:24 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 17:09:45 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec_sum(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.vs[0] = x(v1) + x(v2);
	ret.vs[1] = y(v1) + y(v2);
	ret.vs[2] = z(v1) + z(v2);
	return (ret);
}

t_vec3	vec_sust(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.vs[0] = x(v1) - x(v2);
	ret.vs[1] = y(v1) - y(v2);
	ret.vs[2] = z(v1) - z(v2);
	return (ret);
}

t_vec3	vec_sdiv(t_vec3 v1, t_data denom)
{
	t_vec3	ret;

	ret.vs[0] = x(v1) / denom;
	ret.vs[1] = y(v1) / denom;
	ret.vs[2] = z(v1) / denom;
	return (ret);
}

t_vec3	element_mult(t_vec3 v1, t_vec3 v2)
{
	t_vec3	out;

	out = vec3(v1.vs[0] * v2.vs[0], v1.vs[1] * v2.vs[1], v1.vs[2] * v2.vs[2]);
	return (out);
}

t_vec3	vec_smul(t_vec3 v1, t_data factor)
{
	t_vec3	ret;

	ret.vs[0] = x(v1) * factor;
	ret.vs[1] = y(v1) * factor;
	ret.vs[2] = z(v1) * factor;
	return (ret);
}
