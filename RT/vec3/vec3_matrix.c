/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:09:54 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 17:10:23 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void	vec_matrix_mult(t_vec3 matrix_row, t_vec3 vec, t_vec3 *out, size_t r_i)
{
	t_data	row_value;

	if (!out)
		return ;
	row_value = matrix_row.vs[0] * vec.vs[0];
	row_value += matrix_row.vs[1] * vec.vs[1];
	row_value += matrix_row.vs[2] * vec.vs[2];
	out->vs[r_i] = row_value;
}

t_vec3	rotate(t_vec3 input, t_vec3 degrees)
{
	t_vec3	out;
	t_vec3	tmp;

	degrees = vec_smul(degrees, 3.14159 / 180);
	tmp = input;
	vec_matrix_mult(vec3(1, 0, 0), tmp, &out, 0);
	vec_matrix_mult(vec3(0, cos(x(degrees)), -sin(x(degrees))), tmp, &out, 1);
	vec_matrix_mult(vec3(0, sin(x(degrees)), cos(x(degrees))), tmp, &out, 2);
	tmp = out;
	vec_matrix_mult(vec3(cos(y(degrees)), 0, sin(y(degrees))), tmp, &out, 0);
	vec_matrix_mult(vec3(0, 1, 0), tmp, &out, 1);
	vec_matrix_mult(vec3(-sin(y(degrees)), 0, cos(y(degrees))), tmp, &out, 2);
	tmp = out;
	vec_matrix_mult(vec3(cos(z(degrees)), -sin(z(degrees)), 0), tmp, &out, 0);
	vec_matrix_mult(vec3(sin(z(degrees)), cos(z(degrees)), 0), tmp, &out, 1);
	vec_matrix_mult(vec3(0, 0, 1), tmp, &out, 2);
	return (out);
}
