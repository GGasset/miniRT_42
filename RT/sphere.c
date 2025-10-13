#include "camera.h"
#include "libft.h"
#include "vec3.h"
#include <math.h>
#include <stdio.h>

int	hit_sphere(t_hit_args args)
{
	double		a;
	double		h;
	double		c;
	double		discrim;
	t_vec3		center2r_orig;
	t_object	sphere;

	sphere = args.object;
	center2r_orig = vec_sust(sphere.coords, args.ray.orig);
	// (printf("centr2orig: "), print_vec3(center2r_orig));
	// (printf("direct: "), print_vec3(args->ray.direct));
	a = dot(args.ray.direct, args.ray.direct);
	h = dot(args.ray.direct, center2r_orig);
	c = dot(center2r_orig, center2r_orig) - (sphere.sizes.vs[0]
			* sphere.sizes.vs[0]);
	// printf("a: %lf,  h %lf,  c: %lf\n", a, h, c);
	discrim = h * h - a * c;
	// printf("discrim: %lf\n", discrim);
	args.hit_info->did_hit = 0;
	if (discrim >= 0)
	{
		args.hit_info->distance = (h - sqrt(discrim)) / a;
		args.hit_info->hit_obj = args.object;
		args.hit_info->p = vec_sum(args.ray.orig, vec_smul(args.ray.direct,
					args.hit_info->distance));
		args.hit_info->normal = norm(vec_sust(args.hit_info->p, sphere.coords));
		args.hit_info->did_hit = 1;
	}
	return (args.hit_info->did_hit);
}

// static t_vec3	o_c(t_hit_args args)
// {
// 	return (vec_sust(args.ray.orig, args.object.coords));
// }

// int	hit_sphere(t_hit_args args)
// {
// 	t_data	a;
// 	t_data	b;
// 	t_data	c;
// 	t_data	d;
// 	t_data	delta;

// 	args.hit_info->did_hit = 0;
// 	a = dot(args.ray.direct, args.ray.direct);
// 	b = 2 * (dot(args.ray.direct, o_c(args)));
// 	c = dot(vec_sust(args.ray.orig, args.object.coords), o_c(args))
// 		- pow(args.object.sizes.vs[0], 2);
	
// 	d = 0;
// 	delta = pow(b, 2) - 4 * a * c;
// 	if (delta >= 0)
// 	{
// 		d = (-b + sqrt(delta)) / (2 * a);
// 		if (d < 0)
// 		{
// 			d = (-b - sqrt(delta)) / (2 * a);
// 			if (d < 0)
// 				return (0);
// 		}
// 		args.hit_info->distance = d;
// 		args.hit_info->hit_obj = args.object;
// 		args.hit_info->p = vec_sum(args.ray.orig, vec_smul(args.ray.direct, d));
// 		args.hit_info->normal = norm(vec_sust(args.hit_info->p, args.object.coords));
// 		args.hit_info->did_hit = 1;
// 	}
// 	return (args.hit_info->did_hit);
// }
