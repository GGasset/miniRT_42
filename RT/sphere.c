#include "../Headers/RT_headers/camera.h"
#include "../Headers/RT_headers/vec3.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>

t_data hit_sphere(t_hit_args *args)
{
    const double tmin = 1e-6, tmax = 1e18;

    t_object sphere = { .coords = vec3(0,0,10),
                        .rotation = vec3(0,0,0),
                        .color = vec3(255,255,255) };
    sphere.sizes = malloc(sizeof(t_data));
    sphere.sizes[0] = 4.0; // radio

    t_vec3 c2o = vec_sust(sphere.coords, args->ray.orig); // c - o
    double a   = dot(args->ray.direct, args->ray.direct);
    double h   = dot(args->ray.direct, c2o);              // = - (o-c)·d
    double cc  = dot(c2o, c2o) - sphere.sizes[0]*sphere.sizes[0];
    double D   = h*h - a*cc;

    if (D < 0.0){ args->hit_info->did_hit=0; free(sphere.sizes); return -1.0; }

    double sqD = sqrt(D);
    double t0  = (h - sqD) / a; // raíz menor
    double t1  = (h + sqD) / a; // raíz mayor
    double t   = (t0 >= tmin && t0 <= tmax) ? t0 : t1;
    if (t < tmin || t > tmax){ args->hit_info->did_hit=0; free(sphere.sizes); return -1.0; }

    args->hit_info->did_hit   = 1;
    args->hit_info->distance  = t;
    args->hit_info->hit_obj   = args->object;
    args->hit_info->p         = vec_sum(args->ray.orig, vec_smul(args->ray.direct, t));
    args->hit_info->normal    = norm(vec_sust(args->hit_info->p, sphere.coords));

    free(sphere.sizes);
    return t;
}

