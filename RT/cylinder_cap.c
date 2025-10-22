/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:26:51 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 18:27:04 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_hit_res	hit_cap_0(t_hit_res *res, const t_cap_args *a)
{
	double	dist;

	dist = dot(vec_sust(a->center, a->ray->orig), a->normal);
	if (fabs(dist) < 1e-5 && radial_len2_axis(vec_sust(a->ray->orig, a->center),
			a->normal, 0) <= a->radius * a->radius + 1e-7)
	{
		res->ok = 1;
		res->t = 0.0;
	}
	return (*res);
}

/* =========================
   Tapa individual (struct args)
   ========================= */
t_hit_res	hit_cap(const t_cap_args *a)
{
	t_hit_res	res;
	double		den;
	double		t;
	t_vec3		p;

	res.ok = 0;
	res.t = INFINITY;
	res.n = a->normal;
	den = dot(a->ray->direct, a->normal);
	if (fabs(den) < EPS)
		return (hit_cap_0(&res, a));
	t = dot(vec_sust(a->center, a->ray->orig), a->normal) / den;
	if (t < 0.0)
		return (res);
	p = vec_sum(a->ray->orig, vec_smul(a->ray->direct, t));
	if (radial_len2_axis(vec_sust(p, a->center), a->normal, 0) <= a->radius
		* a->radius + 1e-7)
	{
		res.ok = 1;
		res.t = t;
	}
	return (res);
}
