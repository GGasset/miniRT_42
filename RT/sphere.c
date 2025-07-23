#include "../Headers/RT_headers/camera.h"
#include "../Headers/RT_headers/vec3.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>

t_data	hit_sphere(t_hit_args *args)
{
	double	a;
	double	h;
	double	c;
	double	discrim;
	t_vec3	center2r_orig;
	
	t_object sphere = {
		.coords = vec3(0, 0, 100),               // Plano en el origen
		.rotation = vec3(0, 0, 0),         // Normal apuntando hacia +Y (plano horizontal)
		.color = vec3(255.0, 255.0, 255.0)
	};
	sphere.sizes = malloc(1 * sizeof(t_data));
	sphere.sizes[0] = 4.0;

	center2r_orig = vec_sust(args->object.coords, args->ray.orig);
	a = dot(args->ray.direct, args->ray.direct);
	h = dot(args->ray.direct, center2r_orig);
	c = dot(center2r_orig, center2r_orig) - (sphere.sizes[0] * sphere.sizes[0]);
	discrim = h * h - a * c;
	if (discrim < 0)
	{
		args->hit_info->did_hit = 0;
		free(sphere.sizes);
		return (-1.0);
	}
	else
	{
		args->hit_info->did_hit = 1;
		args->hit_info->distance = (h - sqrt(discrim)) / a;
		args->hit_info->hit_obj = args->object;
		args->hit_info->normal = norm(center2r_orig);
		args->hit_info->p = vec_sum(args->ray.orig, vec_smul(args->ray.direct, args->hit_info->distance));
		free(sphere.sizes);
		return (args->hit_info->distance);
	}
}
