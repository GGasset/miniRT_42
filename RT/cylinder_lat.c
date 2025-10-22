/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_lat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:27:16 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 18:27:17 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

int	lat_setup(t_lat *L, const t_cyl_in *in)
{
	L->r = in->obj->sizes.vs[0] * 0.5;
	L->h = in->obj->sizes.vs[1];
	if (L->r < EPS || L->h < EPS)
		return (0);
	L->n = cylinder_axis(in->obj);
	L->q0 = vec_sust(in->ray->orig, in->obj->coords);
	L->dn = dot(in->ray->direct, L->n);
	L->dp = vec_sust(in->ray->direct, vec_smul(L->n, L->dn));
	L->a = dot(L->dp, L->dp);
	return (1);
}

int	lat_quadratic(t_lat *L)
{
	double	disc;
	double	sd;
	double	inv2a;

	L->qr2 = radial_len2_axis(L->q0, L->n, &L->qp);
	L->b = 2.0 * dot(L->qp, L->dp);
	L->cc = L->qr2 - L->r * L->r;
	disc = L->b * L->b - 4.0 * L->a * L->cc;
	if (disc < 0.0)
		return (0);
	sd = sqrt(fmax(0.0, disc));
	inv2a = 0.5 / L->a;
	L->t0 = (-L->b - sd) * inv2a;
	L->t1 = (-L->b + sd) * inv2a;
	if (L->t0 > L->t1)
	{
		sd = L->t0;
		L->t0 = L->t1;
		L->t1 = sd;
	}
	return (1);
}

t_hit_res	lat_pick_root(const t_cyl_in *in, const t_lat *L)
{
	t_hit_res	res;
	t_vec3		p;
	t_data		t;

	res.ok = 0;
	res.t = INFINITY;
	res.n = vec3(0, 0, 0);
	p = vec3(0, 0, 0);
	t = L->t0;
	if (L->t0 >= 0.0)
	{
		p = vec_sum(in->ray->orig, vec_smul(in->ray->direct, L->t0));
		if (!point_inside_height(in->obj, p))
		{
			p = vec_sum(in->ray->orig, vec_smul(in->ray->direct, L->t1));
			t = L->t1;
		}
		if (point_inside_height(in->obj, p))
		{
			res.ok = 1;
			res.t = t;
			res.n = radial_from_point(in->obj, p);
		}
	}
	return (res);
}

t_hit_res	hit_lateral(const t_cyl_in *in)
{
	t_lat		l;
	t_hit_res	res;

	res.ok = 0;
	if (!lat_setup(&l, in))
		return (res);
	if (l.a < EPS)
		return (res);
	if (!lat_quadratic(&l))
		return (res);
	return (lat_pick_root(in, &l));
}
