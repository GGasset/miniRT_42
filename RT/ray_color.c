#include "../Headers/RT_headers/vec3.h"
#include "../Headers/RT_headers/camera.h"
#include "../libft/libft.h"
#include "stdio.h"

t_color	ray_color(t_ray ray, t_camera camera, t_object_list objs, t_hit_args *args)
{
    t_hit_info info;

    if (world_hit(objs, *args))
		return (args->hit_info->hit_obj.color);
	
	t_vec3 unit = norm(ray.direct);
	t_data	a = 0.5 * (y(unit) + 1.0);
	// return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
	return (vec_sum( vec_smul(vec3(1.0, 1.0, 1.0), 1.0 - a), vec_smul(vec3(0.5, 0.7, 1.0), a)));
}