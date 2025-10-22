/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:10:52 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 18:22:12 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_caps_ctx	caps_ctx_build(const t_object *o)
{
	t_caps_ctx	k;

	k.r = o->sizes.vs[0] * 0.5;
	k.h = o->sizes.vs[1];
	k.n = cylinder_axis(o);
	k.c = o->coords;
	k.ctop = vec_sum(k.c, vec_smul(k.n, 0.5 * k.h));
	k.cbot = vec_sum(k.c, vec_smul(k.n, -0.5 * k.h));
	return (k);
}

t_hit_res	hit_caps(const t_cyl_in *in)
{
	t_caps_ctx	k;
	t_hit_res	a;
	t_hit_res	b;
	t_cap_args	aa;
	t_cap_args	bb;

	k = caps_ctx_build(in->obj);
	a.ok = 0;
	if (k.h < EPS || k.r < EPS)
		return (a);
	aa.ray = in->ray;
	aa.center = k.ctop;
	aa.normal = k.n;
	aa.radius = k.r;
	a = hit_cap(&aa);
	bb.ray = in->ray;
	bb.center = k.cbot;
	bb.normal = vec_smul(k.n, -1.0);
	bb.radius = k.r;
	b = hit_cap(&bb);
	if (!a.ok && !b.ok)
		return (a);
	if (!a.ok || (b.ok && b.t < a.t))
		return (b);
	return (a);
}

/* =========================
   Integración completa
   ========================= */
int	hit_cylinder(t_hit_args args)
{
	t_cyl_in	in;
	t_hit_res	lat;
	t_hit_res	caps;
	t_hit_res	best;

	in.obj = &args.object;
	in.ray = &args.ray;
	lat = hit_lateral(&in);
	caps = hit_caps(&in);
	best = lat;
	if (!best.ok || (caps.ok && caps.t < best.t))
		best = caps;
	args.hit_info->did_hit = 0;
	if (!best.ok)
		return (0);
	args.hit_info->did_hit = 1;
	args.hit_info->hit_obj = args.object;
	args.hit_info->p = vec_sum(args.ray.orig, vec_smul(args.ray.direct,
				best.t));
	args.hit_info->distance = best.t;
	args.hit_info->normal = best.n;
	return (1);
}
