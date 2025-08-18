/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:33:15 by ggasset-          #+#    #+#             */
/*   Updated: 2025/08/18 09:27:30y alvaro           ###   ########.fr       */
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

// static void get_viewport(t_camera c, t_vec3 viewport[2])
// {
//     double ar      = (double)c.width / (double)c.height;
//     double fov_rad = (double)c.fov * 3.14159265359 / 180.0;
//     double w       = 2.0 * c.focal_len * tan(0.5 * fov_rad); // Wv
//     double h       = w / ar;                                  // Hv

//     viewport[0] = vec3(w,  0.0, 0.0);   // right (X)
//     viewport[1] = vec3(0.0, -h,  0.0);  // up (Y negativo para que ↑ sea hacia arriba en pantalla)
// }

// static t_vec3 get_pixel0_pos(t_camera c, t_vec3 delta[2])
// {
//     t_vec3 viewport[2];
//     t_vec3 center, upper_left;

//     get_viewport(c, viewport);
//     delta[0] = vec_sdiv(viewport[0], c.width);
//     delta[1] = vec_sdiv(viewport[1], c.height);

//     center     = vec_sum(c.camera_pos, vec3(0, 0, c.focal_len));                 // +Z
//     upper_left = vec_sum(center, vec_sum(vec_smul(viewport[0], -0.5),            // -W/2
//                                          vec_smul(viewport[1], -0.5)));          // +H/2 (porque viewport[1] es negativo)
//     return vec_sum(upper_left, vec_smul(vec_sum(delta[0], delta[1]), 0.5));
// }


// static t_ray assemble_ray(t_camera camera, t_vec3 pixel_center)
// {
//     t_ray out = ray(camera.camera_pos, vec_sust(pixel_center, camera.camera_pos));
//     out.direct = rotate(out.direct, camera.rotation); // rotate corregida a radianes
//     return out;
// }

/* Base ortonormal desde tu vector de orientación (forward) */
static void camera_frame_from_forward(const t_camera *c,
                                      t_vec3 *fwd, t_vec3 *right, t_vec3 *up)
{
    t_vec3 world_up = vec3(0,1,0);

    *fwd = norm(c->rotation);                 // orientation == forward (unitario)
    if (modulus(*fwd) == 0.0) *fwd = vec3(0,0,1);

    if (fabs(dot(*fwd, world_up)) > 0.99)     // evita degeneración
        world_up = vec3(1,0,0);

    *right = norm(cross_product(*fwd, world_up));
    *up    = norm(cross_product(*right, *fwd));
}

/* Ray per pixel con FOV H y V consistentes (sin “viewport” mundo) */
t_ray create_ray(const t_camera camera, size_t pixel_i)
{
    const double W  = (double)camera.width;
    const double H  = (double)camera.height;
    const double ar = W / H;

    const double fovH = (double)camera.fov * 3.14159265359 / 180.0;  // FOV horizontal
    const double tanH = tan(0.5 * fovH);
    const double tanV = tanH / ar;                        // FOV vertical derivado

    t_vec3 fwd, right, up;
    camera_frame_from_forward(&camera, &fwd, &right, &up);

    const int px = (int)(pixel_i % camera.width);
    const int py = (int)(pixel_i / camera.width);

    /* NDC → cámara (u,v) en “tangente” */
    const double u = ( 2.0 * ((px + 0.5)/W) - 1.0) * tanH;
    const double v = ( 1.0 - 2.0 * ((py + 0.5)/H)) * tanV;

    /* f opcional: si quieres focal_len ≠ 1, multiplica (u,v) y fwd por camera.focal_len */
    t_vec3 dir = norm(vec_sum(vec_smul(fwd, 1.0),
                       vec_sum(vec_smul(right, u),
                               vec_smul(up,    v))));

    return ray(camera.camera_pos, dir);
}
