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
// int hit_cylinder(t_hit_args args)
// {
//     const t_data radius = args.object.sizes.vs[0] * 0.5;
//     t_vec3 c = norm(args.object.rotation);
//     t_vec3 r = norm(args.ray.direct);
//     args.hit_info->did_hit = 0;

//     // Caso paralelo: sin tapas no hay entrada/salida lateral definida
//     if (is_parallel_to_cyl(&args)) {
//         // t_data dist = get_parallel_cyl_dist(&args);
//         // si quieres reportar tangencia dist≈r, aquí podrías marcar hit especial
//         return 0; // sin tapas, lo dejamos como no-hit
//     }

//     // Base auxiliar
//     t_vec3 x = get_ortobase_x(&args);
//     t_vec3 y = get_ortobase_y(&args);

//     // Escalares
//     t_data d    = get_d_segment(&args);       // (or-oc)·x
//     t_data beta = dot(r, y);                  // r·y
//     t_data disc = radius*radius - d*d;        // r^2 - d^2

//     if (disc < 0.0) return 0;                 // no toca la superficie lateral
//     if (fabs(beta) < 1e-9) return 0;          // paralelo a generatrices → sin tapas, no definimos entrada

//     // Dos raíces
//     t_data root = sqrt(disc) / fabs(beta);
//     t_data t1 =  root;
//     t_data t2 = -root;

//     // Menor t >= 0
//     t_data t = -1.0;
//     if (t1 >= 0.0 && t2 >= 0.0) t = fmin(t1, t2);
//     else if (t1 >= 0.0)         t = t1;
//     else if (t2 >= 0.0)         t = t2;
//     if (t < 0.0) return 0;

//     // Punto de impacto
//     t_vec3 p = vec_sum(args.ray.orig, vec_smul(r, t));

//     // Normal lateral: n = normalize(p - q), q = oc + ((p-oc)·c)c
//     t_vec3 oc = args.object.coords;
//     t_vec3 q  = vec_sum(oc, vec_smul(c, dot(vec_sust(p, oc), c)));
//     t_vec3 n  = vec_sdiv(vec_sust(p, q), modulus(vec_sust(p, q)));

//     // Salida
//     args.hit_info->did_hit  = 1;
//     args.hit_info->hit_obj  = args.object;
//     args.hit_info->p        = p;
//     args.hit_info->normal   = n;
//     args.hit_info->distance = t;   // si tu tracer usa t como “distance”

//     return 1;
// }


/* =========================
   Utilidades y constantes
   ========================= */
#ifndef EPS
# define EPS 1e-6
#endif

static inline t_vec3 normalize_safe(t_vec3 v)
{
    double m = modulus(v);
    if (m < EPS) return v;
    return vec_smul(v, 1.0 / m);
}

/* Proyección perpendicular a n (quita componente axial) y su norma^2 */
static inline double radial_len2_from_axis(t_vec3 v, t_vec3 n_unit, t_vec3 *out_radial)
{
    double vn = dot(v, n_unit);
    t_vec3 radial = vec_sust(v, vec_smul(n_unit, vn)); /* v - (v·n) n */
    if (out_radial) *out_radial = radial;
    return dot(radial, radial);
}

/* =========================
   Intersección con una tapa
   ========================= */
static int hit_cylinder_cap(const t_ray ray,
                            t_vec3 cap_center,
                            t_vec3 axis_unit, /* normal del plano de la tapa: ±n */
                            double radius,
                            double *out_t,
                            t_vec3 *out_normal)
{
    const double den = dot(ray.direct, axis_unit);

    /* Rayo ~ paralelo al plano de la tapa */
    if (fabs(den) < EPS) {
        /* ¿Coplanar? */
        const double dist_plane = dot(vec_sust(cap_center, ray.orig), axis_unit);
        if (fabs(dist_plane) < 1e-5) {
            /* ¿El origen cae dentro del disco? => hit con t = 0 */
            double r2 = radial_len2_from_axis(vec_sust(ray.orig, cap_center), axis_unit, NULL);
            if (r2 <= radius * radius + 1e-7) {
                if (out_t)      *out_t = 0.0;
                if (out_normal) *out_normal = axis_unit;
                return 1;
            }
        }
        return 0;
    }

    /* Intersección rayo-plano */
    const double t = dot(vec_sust(cap_center, ray.orig), axis_unit) / den;
    if (t < 0.0) return 0; /* semirango */

    /* Punto candidato */
    const t_vec3 p = vec_sum(ray.orig, vec_smul(ray.direct, t));

    /* ¿Dentro del disco? (quitamos componente axial por robustez) */
    if (radial_len2_from_axis(vec_sust(p, cap_center), axis_unit, NULL) <= radius * radius + 1e-7) {
        if (out_t)      *out_t = t;
        if (out_normal) *out_normal = axis_unit;
        return 1;
    }
    return 0;
}

/* =========================
   Intersección con ambas tapas
   ========================= */
static int hit_cylinder_caps(const t_object obj, const t_ray ray,
                             double *best_t, t_vec3 *best_normal)
{
    const double r = obj.sizes.vs[0] * 0.5;
    const double h = obj.sizes.vs[1];
    if (h < EPS || r < EPS) return 0;

    const t_vec3 n = normalize_safe(obj.rotation);  /* eje unitario */
    const t_vec3 C = obj.coords;                    /* centro del cilindro */
    const t_vec3 C_top = vec_sum(C, vec_smul(n,  0.5 * h));
    const t_vec3 C_bot = vec_sum(C, vec_smul(n, -0.5 * h));

    int    hit = 0;
    double tmin = INFINITY;
    t_vec3 nmin = n;

    /* Tapa superior (normal +n) */
    double t_cap; t_vec3 N_cap;
    if (hit_cylinder_cap(ray, C_top, n, r, &t_cap, &N_cap)) {
        if (t_cap >= 0.0 && t_cap < tmin) {
            tmin = t_cap; nmin = N_cap; hit = 1;
        }
    }

    /* Tapa inferior (normal -n) */
    if (hit_cylinder_cap(ray, C_bot, vec_smul(n, -1.0), r, &t_cap, &N_cap)) {
        if (t_cap >= 0.0 && t_cap < tmin) {
            tmin = t_cap; nmin = N_cap; hit = 1;
        }
    }

    if (!hit) return 0;
    if (best_t)      *best_t = tmin;
    if (best_normal) *best_normal = nmin;
    return 1;
}

/* ================================================
   Intersección con superficie lateral del cilindro
   (cuadrático en el plano perpendicular al eje)
   ================================================ */
static int hit_cylinder_lateral(const t_object obj, const t_ray ray,
                                double *out_t, t_vec3 *out_normal)
{
    const double r = obj.sizes.vs[0] * 0.5;
    const double h = obj.sizes.vs[1];
    if (h < EPS || r < EPS) return 0;

    const t_vec3 n = normalize_safe(obj.rotation);      /* eje unitario */
    const t_vec3 C = obj.coords;
    const t_vec3 O = ray.orig;
    const t_vec3 D = ray.direct;                        /* asume unitario */

    /* Desplazamiento desde centro al origen del rayo */
    const t_vec3 Q0     = vec_sust(O, C);
    const double Dn     = dot(D, n);
    const t_vec3 D_perp = vec_sust(D, vec_smul(n, Dn)); /* D - (D·n) n */
    const double a      = dot(D_perp, D_perp);

    /* Si a ~ 0, D es prácticamente paralelo al eje => el rayo mantiene radio constante */
    if (a < EPS) {
        /* Si el radio constante es > r, no toca lateral; si == r, tangencia (numéricamente inestable) */
        double Q0_r2 = radial_len2_from_axis(Q0, n, NULL);
        if (Q0_r2 > r * r + 1e-7) return 0; /* no toca lateral */
        /* Está dentro o tangente: el primer impacto vendrá por tapas (o tangencia lateral). */
        return 0; /* dejamos que las tapas lo decidan para robustez */
    }

    t_vec3 Q0_perp;
    const double Q0_r2 = radial_len2_from_axis(Q0, n, &Q0_perp); /* |Q0_perp|^2 */
    const double b     = 2.0 * dot(Q0_perp, D_perp);
    const double c     = Q0_r2 - r * r;

    /* Discriminante */
    const double disc = b*b - 4.0*a*c;
    if (disc < 0.0) return 0;

    const double sqrt_disc = sqrt(fmax(0.0, disc));
    const double inv2a     = 0.5 / a;

    /* Raíces ordenadas */
    double t0 = (-b - sqrt_disc) * inv2a;
    double t1 = (-b + sqrt_disc) * inv2a;
    if (t0 > t1) { double tmp = t0; t0 = t1; t1 = tmp; }

    /* Elegimos la menor raíz t >= 0 que además caiga dentro de la altura */
    int    hit = 0;
    double t_best = INFINITY;
    t_vec3 n_best;
	asign_vec3(&n_best, 0,0,0);

    for (int k = 0; k < 2; ++k) {
        double t = (k == 0 ? t0 : t1);
        if (t < 0.0) continue;

        /* Coordenada axial z(t) = dot( (O + tD) - C , n ) */
        double z = dot(vec_sust(vec_sum(O, vec_smul(D, t)), C), n);
        if (z < -0.5 * h - 1e-7 || z > 0.5 * h + 1e-7) continue;

        /* Normal lateral: radial al eje en el punto de impacto */
        t_vec3 P     = vec_sum(O, vec_smul(D, t));
        t_vec3 PmC   = vec_sust(P, C);
        double Pn    = dot(PmC, n);
        t_vec3 radial = vec_sust(PmC, vec_smul(n, Pn)); /* P - proyección sobre eje */
        double m = modulus(radial);
        if (m > EPS) radial = vec_smul(radial, 1.0 / m); /* normaliza */

        if (t < t_best) { t_best = t; n_best = radial; hit = 1; }
    }

    if (!hit) return 0;
    if (out_t)      *out_t = t_best;
    if (out_normal) *out_normal = n_best;
    return 1;
}

/* =========================
   Integración completa
   ========================= */
int hit_cylinder(t_hit_args args)
{
    t_object obj = args.object;

    /* Candidatos: lateral y tapas */
    double t_lat = 0, t_cap;
    t_vec3 n_lat, n_cap;
    int    has_lat = hit_cylinder_lateral(obj, args.ray, &t_lat, &n_lat);
    int    has_cap = hit_cylinder_caps(obj, args.ray, &t_cap, &n_cap);

    /* Elige el primer impacto (mínimo t >= 0) */
    int    hit = 0;
    double t_best = INFINITY;
    t_vec3 n_best;
	
	asign_vec3(&n_best, 0,0,0);
    if (has_lat && t_lat >= 0.0 && t_lat < t_best) { t_best = t_lat; n_best = n_lat; hit = 1; }
    if (has_cap && t_cap >= 0.0 && t_cap < t_best) { t_best = t_cap; n_best = n_cap; hit = 1; }

    /* Rellenar hit_info si hay impacto */
    args.hit_info->did_hit = 0;
    if (!hit) return 0;

    args.hit_info->did_hit  = 1;
    args.hit_info->hit_obj  = obj;
    args.hit_info->p        = vec_sum(args.ray.orig, vec_smul(args.ray.direct, t_best));
    args.hit_info->distance = t_best;
    args.hit_info->normal   = n_best;
    return 1;
}


