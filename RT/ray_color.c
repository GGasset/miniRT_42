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
#include "minilibx_funcs.h"
#include "libft.h"
#include "stdio.h"

static t_data	sample_shadows(t_hit_args ray, t_object_list objs)
{
	t_hit_args	args_copy;
	size_t		n_hits;
	size_t		n_samples;
	size_t		i;

	n_samples = 10;
	n_hits = 0;
	i = 0;
	while (i < n_samples)
	{
		args_copy = ray;
		args_copy.ray.direct = small_direction_shift(args_copy.ray.direct);
		if (world_hit(objs, args_copy))
			n_hits++;
		i++;
	}
	return (1 - (t_data)n_hits / n_samples);
}

static t_data	reflect_multiplier(t_hit_args args, t_ray r, t_light l)
{
	t_vec3	light_direction;
	t_vec3	bounced_ray_dir;
	t_vec3	tmp;
	t_data	out;
	
	light_direction = norm(vec_sust(l.coords, args.hit_info->p));
	tmp = norm(args.hit_info->normal);
	//print_vec3(tmp);
	//printf("%f\n", modulus(tmp));
	bounced_ray_dir = get_bounce(args).direct;
	return (1 - modulus(vec_sust(light_direction, bounced_ray_dir)) / 1);
	//out = modulus(vec_sust(light_direction, tmp));
	//printf("%f\n", out);
	return (1 - out);
}

t_color	point_ilum(t_color c, t_hit_args info, t_scene s, t_light l, t_ray r)
{
	t_vec3		light_direction;
	t_hit_info	hit_info;
	t_hit_args	hit_args;

	ft_bzero(&hit_info, sizeof(t_hit_info));
	ft_bzero(&hit_args, sizeof(t_hit_args));
	light_direction = norm(vec_sust(l.coords, info.hit_info->p));
	l.brightness *= info.hit_info->distance / 20;
	//l.brightness *= (190 - vec_angle(light_direction, info.hit_info->normal)) / 180;
	//l.brightness *= reflect_multiplier(info, r, l);

	hit_args.hit_info = &hit_info;
	hit_args.ray.orig = vec_sum(info.hit_info->p, vec_smul(info.hit_info->normal, .5));
	hit_args.ray.direct = light_direction;
	hit_args.ray.direct = hit_args.ray.direct;
	hit_args.distance_range.min = 0;
	hit_args.distance_range.max = modulus(vec_sust(info.hit_info->p, l.coords));
	l.brightness *= sample_shadows(hit_args, s.objects);
	return (iluminate(c, info.hit_info->hit_obj.color, l));
}

t_color	iluminate(t_color current, t_color object_color, t_light light)
{
	t_vec3	object_rgb;
	t_vec3	light_rgb;
	t_vec3	out_rgb;

	light.brightness += (1 - light.brightness) * (light.brightness > 1)
		- light.brightness * (light.brightness < 0);
	object_rgb = get_rgb(object_color);
	light_rgb = get_rgb(light.color);
	out_rgb = element_mult(vec_sdiv(object_rgb, 255), vec_sdiv(light_rgb, 255));
	out_rgb = vec_smul(out_rgb, light.brightness * 255);
	out_rgb = vec_sum(get_rgb(current), out_rgb);
	out_rgb.vs[0] += (255 - out_rgb.vs[0]) * (out_rgb.vs[0] > 255)
		- out_rgb.vs[0] * (out_rgb.vs[0] < 0);
	out_rgb.vs[1] += (255 - out_rgb.vs[1]) * (out_rgb.vs[1] > 255)
		- out_rgb.vs[1] * (out_rgb.vs[1] < 0);
	out_rgb.vs[2] += (255 - out_rgb.vs[2]) * (out_rgb.vs[2] > 255)
		- out_rgb.vs[2] * (out_rgb.vs[2] < 0);
	return (get_color(out_rgb));
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
