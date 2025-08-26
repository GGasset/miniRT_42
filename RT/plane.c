
#include "../Headers/RT_headers/camera.h"
#include "../Headers/RT_headers/vec3.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>

/*
	- En object->rotation está el vector normal
	- El vector normal codifica los coeficientes
	  de las dimensiones del plano (A, B, C).
	- El punto que pertenence al plano está object->coords.
	
	La cuestión consiste en determinar si existe algún t
	para que de una posición en la recta que coincida con
	un punto del plano.


*/
int	hit_plane(t_hit_args args)
{
	t_data		numerator;
	t_data		denominator;
	t_data		t;
	t_object	obj;

	obj = args.object;
	numerator = dot(obj.rotation, vec_sust(args.ray.orig, obj.coords));
	denominator = dot(obj.rotation, args.ray.direct);
	printf("num: %lf  demon: %lf\n", numerator, denominator);

	if (fabs(denominator) < 1e-6)
		return (-1.0); // El rayo es paralelo al plano
	t = numerator / denominator;
	args.hit_info->did_hit = 0;
	if (t >= 0)
	{
		args.hit_info->did_hit = 1;
		args.hit_info->hit_obj = args.object;
		args.hit_info->p = vec_sum(vec_smul(args.ray.direct, t),
									args.ray.orig);
		// args->hit_info->distance = modulus(args->hit_info->p); //Mal
		args.hit_info->distance = t;
		args.hit_info->normal = obj.rotation;
	}
	return (args.hit_info->did_hit);
}

/*int main(void)
{
	t_object plane = {
		.coords = vec3(0, 0, 0),               // Plano en el origen
		.rotation = vec3(0, 1, 0)              // Normal apuntando hacia +Y (plano horizontal)
	};

	t_ray ray = {
		.orig = vec3(0, 10, 0),                // Empieza 10 unidades sobre el plano
		.direct = norm(vec3(0, 1, 0)) // Apunta hacia abajo
	};

	t_hit_info hit_info;
	t_hit_args args = {plane, {0.0, 18.0}, ray, &hit_info};

	double t = hit_plane(&args);
	printf("t: %lf\n", t);

	if (hit_info.did_hit)
	{
		printf("Impacto a t = %.2f\n", t);
		printf("Punto de impacto: (%.2f, %.2f, %.2f)\n",
			hit_info.p.vs[0], hit_info.p.vs[1], hit_info.p.vs[2]);
	}
	else
	{
		printf("No hay impacto con el plano\n");
	}

	return 0;
}*/
