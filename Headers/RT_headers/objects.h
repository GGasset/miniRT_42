/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:23:20 by ggasset-          #+#    #+#             */
/*   Updated: 2025/10/22 18:22:30 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"

enum	e_object
{
	Sphere,
	Cylinder,
	Plane,
};

typedef struct t_hit_args	t_hit_args;
typedef struct t_hit_info	t_hit_info;

typedef struct t_object
{
	t_point3		coords;
	t_rotation		rotation;
	t_color			color;
	t_vec3			sizes;
	enum e_object	kind;
	int				(*hit)(t_hit_args hit_args);
}		t_object;

t_object	object(enum e_object kind);

typedef struct t_object_list
{
	t_object	*objs;
	size_t		len;
}		t_object_list;

void		free_object_list(t_object_list list);

/*
### Distance (a.k.a. t)
*/
typedef struct t_hit_info
{
	t_point3	p;
	t_vec3		normal;
	t_data		distance;
	t_object	hit_obj;
	int			did_hit;
}		t_hit_info;

typedef struct t_hit_args
{
	t_object	object;
	t_interval	distance_range;
	t_ray		ray;
	t_hit_info	*hit_info;
}		t_hit_args;

/* 
			CYlinder
*/

# ifndef EPS
#  define EPS 1e-6
# endif

typedef struct s_hit_res
{
	int		ok;
	double	t;
	t_vec3	n;
}	t_hit_res;

typedef struct s_cyl_in
{
	const t_object	*obj;
	const t_ray		*ray;
}	t_cyl_in;

typedef struct s_cap_args
{
	const t_ray	*ray;
	t_vec3		center;
	t_vec3		normal;
	double		radius;
}	t_cap_args;

typedef struct s_caps_ctx
{
	double			r;
	double			h;
	t_vec3			n;
	t_vec3			c;
	t_vec3			ctop;
	t_vec3			cbot;
}					t_caps_ctx;

/* =========================
   Lateral (usa structs)
   ========================= */
typedef struct s_lat
{
	double			r;
	double			h;
	double			dn;
	double			a;
	double			qr2;
	double			b;
	double			cc;
	double			t0;
	double			t1;
	t_vec3			n;
	t_vec3			q0;
	t_vec3			dp;
	t_vec3			qp;
}					t_lat;

int			hit_cylinder(t_hit_args args);
t_hit_res	hit_caps(const t_cyl_in *in);
t_hit_res	hit_cap(const t_cap_args *a);
t_caps_ctx	caps_ctx_build(const t_object *o);
t_hit_res	hit_lateral(const t_cyl_in *in);
t_hit_res	lat_pick_root(const t_cyl_in *in, const t_lat *L);
int			lat_quadratic(t_lat *L);
int			lat_setup(t_lat *L, const t_cyl_in *in);
t_vec3		normalize_safe(t_vec3 v);
double		radial_len2_axis(t_vec3 v, t_vec3 n, t_vec3 *out);
t_vec3		cylinder_axis(const t_object *o);
int			point_inside_height(const t_object *o, t_vec3 p);
t_vec3		radial_from_point(const t_object *o, t_vec3 p);


int			hit_sphere(t_hit_args args);
int			hit_plane(t_hit_args args);
int			world_hit(t_object_list world_objs, t_hit_args args);

#endif
