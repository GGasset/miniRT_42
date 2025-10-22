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

static t_data	reflect_multiplier(t_hit_args args, t_light l)
{
	t_data	refl_coeff;
	t_vec3	light_direction;
	t_vec3	bounced_ray_dir;
	t_vec3	tmp;
	t_data	out[3];

	refl_coeff = .4;
	light_direction = norm(vec_sust(l.coords, args.hit_info->p));
	bounced_ray_dir = norm(get_bounce(args).direct);
	tmp = norm(args.hit_info->normal);
	out[0] = 0;
	out[1] = 0;
	out[0] = 1 - (vec_angle(bounced_ray_dir, light_direction) / (144));
	out[0] += -out[0] * (out[0] < 0) + (1 - out[0]) * (out[0] > 1);
	out[1] = 1 - (vec_angle(tmp, light_direction) / 90);
	out[1] += -out[1] * (out[1] < 0) + (1 - out[1]) * (out[1] > 1);
	out[2] = out[0] + out[1];
	out[2] += -out[2] * (out[2] < 0) + (1 - out[2]) * (out[1] > 1);
	out[2] += rand_fract(TRUE) * .0103125;
	return (out[2]);
}

t_color	point_ilum(t_color c, t_hit_args info, t_scene s, t_light l)
{
	t_vec3		light_direction;
	t_hit_info	hit_info;
	t_hit_args	hit_args;

	ft_bzero(&hit_info, sizeof(t_hit_info));
	ft_bzero(&hit_args, sizeof(t_hit_args));
	light_direction = norm(vec_sust(l.coords, info.hit_info->p));
	l.brightness *= reflect_multiplier(info, l);

	hit_args.hit_info = &hit_info;
	hit_args.ray.orig = vec_sum(l.coords,
		vec_smul(info.hit_info->normal, EPSILON));
	hit_args.ray.direct = norm(vec_sust(info.hit_info->p, l.coords));
	hit_args.distance_range.min = EPSILON;
	hit_args.distance_range.max =
		modulus(vec_sust(info.hit_info->p, l.coords)) - EPSILON;
	l.brightness *= !world_hit(s.objects, hit_args);
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
