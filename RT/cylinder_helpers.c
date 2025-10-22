/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:26:08 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 18:26:46 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/* =========================
   Helpers básicos
   ========================= */
t_vec3	normalize_safe(t_vec3 v)
{
	double	m;

	m = modulus(v);
	if (m < EPS)
		return (v);
	return (vec_smul(v, 1.0 / m));
}

double	radial_len2_axis(t_vec3 v, t_vec3 n, t_vec3 *out)
{
	double	vn;
	t_vec3	rad;

	vn = dot(v, n);
	rad = vec_sust(v, vec_smul(n, vn));
	if (out)
		*out = rad;
	return (dot(rad, rad));
}

t_vec3	cylinder_axis(const t_object *o)
{
	return (normalize_safe(o->rotation));
}

int	point_inside_height(const t_object *o, t_vec3 p)
{
	t_vec3	n;
	double	z;

	n = cylinder_axis(o);
	z = dot(vec_sust(p, o->coords), n);
	return (!(z < -0.5 * o->sizes.vs[1] - 1e-7 || z > 0.5 * o->sizes.vs[1]
			+ 1e-7));
}

t_vec3	radial_from_point(const t_object *o, t_vec3 p)
{
	t_vec3	n;
	t_vec3	v;
	double	s;
	t_vec3	r;

	n = cylinder_axis(o);
	v = vec_sust(p, o->coords);
	s = dot(v, n);
	r = vec_sust(v, vec_smul(n, s));
	s = modulus(r);
	if (s > EPS)
		r = vec_smul(r, 1.0 / s);
	return (r);
}
