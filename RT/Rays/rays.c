/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:08:48 by ggasset-          #+#    #+#             */
/*   Updated: 2025-06-05 13:08:48 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_ray ray(t_point3 position, t_rotation direction)
{
	t_ray	out;

	out.orig = position;
	out.direct = direction;
	return out;
}

t_ray	create_ray(t_camera camera, size_t pixel_i)
{
	t_data	viewport_len[2];
	t_vec3	viewport[2];
	t_vec3	pixel_delta[2];
	t_vec3	viewport_upper_left[2];
	t_vec3	out_direction;

	viewport_len[1] = 2.0;
	viewport_len[0] = viewport_len[0] * ((t_data)camera.width / camera.height);
	viewport[0] = vec3(viewport_len[0], 0, 0);
	viewport[1] = vec3(0, -viewport_len[1], 0);
	pixel_delta[0] = vec_sdiv(viewport[0], camera.width);
	pixel_delta[1] = vec_sdiv(viewport[1], camera.height);
	viewport_upper_left[0] = vec_sust(vec_sust(vec_sust(camera.camera_pos,
					vec3(0, 0, 1)), vec_sdiv(viewport[0], 2)),
			vec_sdiv(viewport[1], 2));
	viewport_upper_left[1] = vec_smul(vec_sum(viewport[0], viewport[1]), .5);
	out_direction = vec_sum(vec_sum(viewport_upper_left[1],
		vec_smul(pixel_delta[0], pixel_i % camera.width)),
		vec_smul(pixel_delta[1], pixel_i / camera.width));
	return (ray(camera.camera_pos, out_direction));
}
