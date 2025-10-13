/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:33:15 by ggasset-          #+#    #+#             */
/*   Updated: 2025/09/16 14:05:04y alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_ray	ray(t_point3 position, t_rotation direction)
{
	t_ray	out;

	out.orig = position;
	out.direct = direction;
	return (out);
}

static void get_viewport(t_camera cam, t_vec3 viewport[2])
{
	double	aspect_ratio;
	double	h;
	double	viewport_width;

	if (!viewport)
		return ;
	aspect_ratio = (double)cam.width / cam.height;
	h = tan(cam.fov * 3.14159 / 180 / 2);
	viewport_width = 2.0 * aspect_ratio * 2 * h * cam.focal_len;
	viewport[0] = vec3(viewport_width, 0, 0);
	viewport[1] = vec3(0, -(viewport_width / aspect_ratio), 0);
}

static t_vec3	get_pixel0_pos(t_camera c, t_vec3 delta[2])
{
	t_vec3	viewport[2];
	t_vec3	upper_left;
	t_vec3	upper_left_pixel_pos;

	get_viewport(c, viewport);
	delta[0] = vec_sdiv(viewport[0], c.width);
	delta[1] = vec_sdiv(viewport[1], c.height);
	upper_left = vec3(0, 0, 1);
	upper_left = element_mult(upper_left, c.rotation);
	upper_left = vec_sust(c.camera_pos, upper_left);
	upper_left = vec_sust(upper_left, vec_sdiv(viewport[0], 2));
	upper_left = vec_sust(upper_left, vec_sdiv(viewport[1], 2));
	upper_left_pixel_pos = vec_sum(upper_left, vec_smul(
				vec_sum(delta[0], delta[1]), .5));
	return (upper_left_pixel_pos);
}

static t_ray	assemble_ray(t_camera camera, t_vec3 pixel_center)
{
	t_ray		out;
	t_rotation	degrees;

	out = ray(camera.camera_pos, vec_sust(pixel_center, camera.camera_pos));
	degrees = get_angles(vec3(0, 0, -1), norm(camera.rotation));
	degrees.vs[0] = 0;
	out.direct = norm(rotate(out.direct, degrees));
	return (out);
}

t_ray	create_ray(t_camera camera, size_t pixel_i)
{
	t_vec3	pixel_delta[2];
	t_vec3	pixel_center;
	t_vec3	pixel0_pos;

	pixel0_pos = get_pixel0_pos(camera, pixel_delta);
	pixel_center = vec_sum(vec_sum(pixel0_pos,
		vec_smul(pixel_delta[0], pixel_i % camera.width)),
		vec_smul(pixel_delta[1], pixel_i / camera.width));
	return (assemble_ray(camera, pixel_center));
}
