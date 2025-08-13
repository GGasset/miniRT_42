/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:33:15 by ggasset-          #+#    #+#             */
/*   Updated: 2025/08/13 18:49:30 by alvmoral         ###   ########.fr       */
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

static void get_viewport(t_camera c, t_vec3 viewport[2])
{
    double ar      = (double)c.width / (double)c.height;
    double fov_rad = (double)c.fov * 3.14159265359 / 180.0;
    double w       = 2.0 * c.focal_len * tan(0.5 * fov_rad); // Wv
    double h       = w / ar;                                  // Hv

    viewport[0] = vec3(w,  0.0, 0.0);   // right (X)
    viewport[1] = vec3(0.0, -h,  0.0);  // up (Y negativo para que ↑ sea hacia arriba en pantalla)
}

static t_vec3 get_pixel0_pos(t_camera c, t_vec3 delta[2])
{
    t_vec3 viewport[2];
    t_vec3 center, upper_left;

    get_viewport(c, viewport);
    delta[0] = vec_sdiv(viewport[0], c.width);
    delta[1] = vec_sdiv(viewport[1], c.height);

    center     = vec_sum(c.camera_pos, vec3(0, 0, c.focal_len));                 // +Z
    upper_left = vec_sum(center, vec_sum(vec_smul(viewport[0], -0.5),            // -W/2
                                         vec_smul(viewport[1], -0.5)));          // +H/2 (porque viewport[1] es negativo)
    return vec_sum(upper_left, vec_smul(vec_sum(delta[0], delta[1]), 0.5));
}


static t_ray assemble_ray(t_camera camera, t_vec3 pixel_center)
{
    t_ray out = ray(camera.camera_pos, vec_sust(pixel_center, camera.camera_pos));
    out.direct = rotate(out.direct, camera.rotation); // rotate corregida a radianes
    return out;
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
