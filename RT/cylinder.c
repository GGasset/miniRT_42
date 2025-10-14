/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:40:45 by ggasset-          #+#    #+#             */
/*   Updated: 2025/10/14 11:23:25by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

// Does not make the actual sqrt, just the inner part
// static t_data	calculate_quadratic_sqrt(t_hit_args args)
// {
// 	t_vec3	nxa;
// 	t_data	r;
// 	t_data	tmp;
// 	t_data	out;

// 	r = args.object.sizes.vs[0] / 2;
// 	nxa = cross_product(args.ray.direct, args.object.rotation);
// 	if (!modulus(nxa))
// 		return (-1);
// 	out = dot(nxa, nxa) * r * r;
// 	tmp = dot(vec_sust(args.object.coords, args.ray.orig), nxa);
// 	tmp *= tmp;
// 	out -= dot(args.object.rotation, args.object.rotation) * tmp;
// 	return (out);
// }

// static void	quadratic(t_data *out_d, t_hit_args args, t_data sqrt_in)
// {
// 	t_vec3	nxa;
// 	t_data	nxanxa;
// 	t_vec3	b;
// 	t_data	before_sqrt;
// 	t_data	solutions[2];

// 	b = vec_sust(args.object.coords, args.ray.orig);
// 	nxa = cross_product(args.ray.direct, args.object.rotation);
// 	nxanxa = dot(nxa, nxa);
// 	before_sqrt = dot(nxa, cross_product(b, args.object.rotation));
// 	solutions[0] = (before_sqrt + sqrt(sqrt_in)) / nxanxa;
// 	solutions[1] = (before_sqrt - sqrt(sqrt_in)) / nxanxa;
// 	*out_d = solutions[0] * (solutions[0] <= solutions[1]);
// 	*out_d += solutions[1] * (solutions[0] > solutions[1]);
// }

// // Does not include end caps
// static int	calculate_cylinder(t_hit_args args, t_hit_info *out_data)
// {
// 	t_data	sqrt_in;
// 	t_data	t;
// 	t_vec3	tmp;

// 	if (!out_data)
// 		return (0);
// 	sqrt_in = calculate_quadratic_sqrt(args);
// 	if (sqrt_in < 0)
// 		return (0);
// 	quadratic(&out_data->distance, args, sqrt_in);
// 	out_data->p = vec_sum(args.ray.orig, vec_smul(args.ray.direct, out_data->distance));
// 	t = dot(args.object.rotation, vec_sust(out_data->p, vec_sust(args.object.coords, args.ray.orig)));
// 	if (t < 0 || t > args.object.sizes.vs[1])
// 		return (0);
// 	out_data->did_hit = 1;
// 	tmp = vec_smul(args.object.rotation, -t);
// 	tmp = vec_sum(tmp, vec_smul(args.ray.direct, out_data->distance));
// 	out_data->normal = norm(vec_sum(tmp, args.object.coords));
// 	out_data->hit_obj = args.object;
// 	return (out_data->did_hit);
// }

// static int	calculate_caps(t_hit_args args, t_hit_info *out, int is_end_cap)
// {
// 	t_vec3	c;
// 	t_vec3	b;
// 	t_vec3	nd;
// 	t_data	d;
// 	t_data	r;

// 	r = x(args.object.sizes) / 2;
// 	b = vec_sust(args.object.coords, args.ray.orig);
// 	is_end_cap = is_end_cap != 0;
// 	c = vec_sum(b, vec_smul(vec_smul(args.object.rotation,
// 					y(args.object.sizes)), is_end_cap));
// 	d = dot(args.object.rotation, c)
// 		/ dot(args.object.rotation, args.ray.direct);
// 	nd = vec_smul(args.ray.direct, d);
// 	if (dot(vec_sust(nd, c), vec_sust(nd, c)) >= r * r)
// 		return (0);
// 	out->did_hit = 1;
// 	out->distance = d;
// 	out->hit_obj = args.object;
// 	out->normal = norm(vec_smul(args.object.rotation, 1 - 2 * (!is_end_cap)));
// 	return (1);
// }

// int	hit_cylinder(t_hit_args args)
// {
// 	t_hit_info	tmp[3];
// 	t_hit_info	closest_hit;
// 	int			did_hit;
// 	int			is_closer;
// 	size_t		i;

// 	args.object.rotation = norm(args.object.rotation);
// 	ft_bzero(&closest_hit, sizeof(t_hit_info));
// 	ft_bzero(&tmp, sizeof(t_hit_info) * 3);
// 	did_hit = calculate_cylinder(args, &tmp[0]);
// 	did_hit = calculate_caps(args, &tmp[1], 0) || did_hit;
// 	did_hit = calculate_caps(args, &tmp[2], 1) || did_hit;
// 	if (!did_hit)
// 		return (0);
// 	closest_hit.distance = args.distance_range.max + 1;
// 	i = 0;
// 	while (i < 3)
// 	{
// 		is_closer = tmp[i].did_hit && tmp[i].distance > args.distance_range.min;
// 		if (is_closer && (tmp[i].distance < closest_hit.distance))
// 			closest_hit = tmp[i];
// 		i++;
// 	}
// 	*args.hit_info = closest_hit;
// 	return (args.hit_info->did_hit);
// }

t_vec3	get_ortobase_x(t_hit_args *args)
{
	t_vec3	c;
	t_vec3	r;
	
	c = args->object.rotation;
	r = args->ray.direct;
	return (norm(cross_product(c, r)));
}

t_vec3	get_ortobase_z(t_hit_args *args)
{
	t_vec3	c;

	c = args->object.rotation;
	return (norm(c));
}

t_vec3	get_ortobase_y(t_hit_args *args)
{
	return (norm(cross_product(
		get_ortobase_z(args),
		get_ortobase_x(args)
	)));
}

t_data	get_d_segment(t_hit_args *args)
{
	t_vec3	oc;
	t_vec3	or;
	t_vec3	x;
	t_data	dot_projection_onto_x;

	oc = args->object.coords;
	or = args->ray.orig;
	x = get_ortobase_x(args);
	dot_projection_onto_x = dot(vec_sust(or, oc), x);
	return (dot_projection_onto_x);
	// return (vec_smul(x, dot_projection_onto_x));
}

int is_parallel_to_cyl(const t_hit_args *args)
{
    t_vec3 c = norm(args->object.rotation);
    t_vec3 r = norm(args->ray.direct);
    double s = modulus(cross_product(c, r)); // 0 si paralelos
    return (s < 1e-6);
}


t_data	get_parallel_cyl_dist(t_hit_args *args)
{
	t_vec3	oc;
	t_vec3	or;
	t_vec3	c;
	t_data	dot_projection_onto_c;
	t_vec3	projection_onto_c;

	c = args->object.rotation;
	oc = args->object.coords;
	or = args->ray.orig;
	dot_projection_onto_c = dot(
		vec_sust(or, oc),
		c
	);
	projection_onto_c = vec_smul(c, dot_projection_onto_c);
	return (modulus(
		vec_sust(
			vec_sust(or, oc),
			projection_onto_c)));
}

t_vec3	get_ortanormal_o(t_hit_args *args, t_data beta, t_data d)
{
	t_data	t0;
	t_vec3	oc;
	t_vec3	or;
	
	oc = args->object.coords;
	or = args->ray.orig;
	t0 = dot(vec_sust(oc, or), get_ortobase_y(args));
	t0 /= beta;
	return (ft_vecop(2, or, '+', 
			vec_smul(args->ray.direct, t0), '-',
			vec_smul(get_ortobase_x(args), d)));
}

// int	hit_cylinder(t_hit_args args)
// {
// 	t_vec3	radius;
// 	t_data	d;
// 	t_data	beta;
// 	t_data	discrim;
// 	t_data	t;
// 	t_vec3	p;
// 	t_vec3	q;
// 	t_data	z;
// 	t_vec3 c;
// 	t_vec3 oc;
	
// 	t_vec3 c = norm(args.object.rotation);
// 	t_vec3 oc = args.object.coords;
// 	args.hit_info->did_hit = 0;
// 	if (is_parallel_to_cyl(&args))
// 	{
// 		discrim = get_parallel_cyl_dist(&args);
// 		args.hit_info->did_hit = discrim <= (args.object.sizes.vs[0] / 2);
// 		if (args.hit_info->did_hit > args.object.sizes.vs[0] / 2)
// 			return (0);
		
// 	}
// 	else
// 	{
// 		// d = dot(get_d_segment(&args), get_ortobase_x(&args));
// 		d = get_d_segment(&args);
// 		beta = dot(args.ray.direct, get_ortobase_y(&args));
// 		discrim = (pow(args.object.sizes.vs[0], 2) / 4) - (d * d);
// 		if (discrim < 0)
// 			return (0);
// 		// if (fabs(beta) < 0.00001)
// 			//Vainas
// 		t = sqrt(discrim / (beta * beta));
// 		args.hit_info->did_hit = 0;
// 		p = ft_vecop(1, args.ray.orig, '+',
// 					vec_smul(args.ray.direct, t));
// 		// z = dot(ft_vecop(1, p, '-', args.object.coords), args.object.rotation);
// 		q = vec_sum(oc, vec_smul(c, dot(vec_sust(p, oc), c)));
// 		args.hit_info->p = p;
// 		args.hit_info->normal = vec_sdiv(ft_vecop(1, p, '-', q),
// 										(modulus(ft_vecop(1, p, '-', q))));
// 	}

// }

// === Hit lateral sin tapas ===
int hit_cylinder(t_hit_args args)
{
    const t_data radius = args.object.sizes.vs[0] * 0.5;
    t_vec3 c = norm(args.object.rotation);
    t_vec3 r = norm(args.ray.direct);
    args.hit_info->did_hit = 0;

    // Caso paralelo: sin tapas no hay entrada/salida lateral definida
    if (is_parallel_to_cyl(&args)) {
        // t_data dist = get_parallel_cyl_dist(&args);
        // si quieres reportar tangencia dist≈r, aquí podrías marcar hit especial
        return 0; // sin tapas, lo dejamos como no-hit
    }

    // Base auxiliar
    t_vec3 x = get_ortobase_x(&args);
    t_vec3 y = get_ortobase_y(&args);

    // Escalares
    t_data d    = get_d_segment(&args);       // (or-oc)·x
    t_data beta = dot(r, y);                  // r·y
    t_data disc = radius*radius - d*d;        // r^2 - d^2

    if (disc < 0.0) return 0;                 // no toca la superficie lateral
    if (fabs(beta) < 1e-9) return 0;          // paralelo a generatrices → sin tapas, no definimos entrada

    // Dos raíces
    t_data root = sqrt(disc) / fabs(beta);
    t_data t1 =  root;
    t_data t2 = -root;

    // Menor t >= 0
    t_data t = -1.0;
    if (t1 >= 0.0 && t2 >= 0.0) t = fmin(t1, t2);
    else if (t1 >= 0.0)         t = t1;
    else if (t2 >= 0.0)         t = t2;
    if (t < 0.0) return 0;

    // Punto de impacto
    t_vec3 p = vec_sum(args.ray.orig, vec_smul(r, t));

    // Normal lateral: n = normalize(p - q), q = oc + ((p-oc)·c)c
    t_vec3 oc = args.object.coords;
    t_vec3 q  = vec_sum(oc, vec_smul(c, dot(vec_sust(p, oc), c)));
    t_vec3 n  = vec_sdiv(vec_sust(p, q), modulus(vec_sust(p, q)));

    // Salida
    args.hit_info->did_hit  = 1;
    args.hit_info->hit_obj  = args.object;
    args.hit_info->p        = p;
    args.hit_info->normal   = n;
    args.hit_info->distance = t;   // si tu tracer usa t como “distance”

    return 1;
}

