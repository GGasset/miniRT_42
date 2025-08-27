/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-27 11:32:47 by ggasset-          #+#    #+#             */
/*   Updated: 2025-08-27 11:32:47 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "camera.h"
#include "libft.h"
#include "stdio.h"

t_color	shift(t_color old, t_color target, t_data factor, int reflects)
{
	int	r;
	int	g;
	int	b;

	if (!old)
		return (target);
	reflects = reflects != 0;
	factor += (1 - factor) * (factor > 1) - factor * (factor < 0);
	b = old & 255;
	g = (old & (255 << 8)) >> 8;
	r = (old & (255 << 16)) >> 16;
	r += ((target & 255) - r * reflects) * factor * ((r / 255.) * !reflects);
	g += (((target & (255 << 8)) >> 8) - g * reflects) * factor
		* ((g / 255.) * !reflects);
	b += (((target & (255 << 16)) >> 16) - b * reflects) * factor
		* ((b / 255.) * !reflects);
	r += (255 - r) * (r > 255) - r * (r < 0);
	g += (255 - g) * (g > 255) - g * (g < 0);
	b += (255 - b) * (b > 255) - b * (b < 0);
	return ((0xFF << 24) + (r << 16) + (g << 8) + b);
}

t_color	get_sky_color(t_camera camera, size_t pixel_y)
{
	int	out;
	int	to_add;

	out = 0xFF154f8c;
	to_add = (255 - (out & 255)) * pixel_y / (t_data)camera.height / 1.8;
	out += (to_add << 16) + (to_add << 8) + to_add;
	return (out);
}

/*t_color	ray_color(t_ray ray, t_camera camera, t_object_list objs, t_hit_args *args)
{
    t_hit_info info;

    if (world_hit(objs, *args))
		return (args->hit_info->hit_obj.color);
	
	t_vec3 unit = norm(ray.direct);
	t_data	a = 0.5 * (y(unit) + 1.0);
	// return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
	return (vec_sum( vec_smul(vec3(1.0, 1.0, 1.0), 1.0 - a), vec_smul(vec3(0.5, 0.7, 1.0), a)));
}*/