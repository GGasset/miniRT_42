/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:42:57 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 12:33:42 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/RT_headers/camera.h"
#include "../../Headers/minilibx_funcs.h"

void	fill_ambient_ligth(t_light *ambient, char **argv)
{
	asign_vec3(&ambient->coords, 0.0, 0.0, 0.0);
	ambient->brightness = get_scalar(*argv++);
	ambient->color = get_color(get_vector(*argv++));
}

void	fill_ligth(t_light *light, char **argv)
{
	light->coords = get_vector(*argv++);
	light->brightness = get_scalar(*argv++);
	light->color = get_color(get_vector(*argv++));
}

/*
	∗ identifier: C
	∗ x, y, z coordinates of the viewpoint: -50.0,0,20
	∗ 3D normalized orientation vector, in the range [-1,1] for each x, y,
		z axis:
	0.0,0.0,1.0
	∗ FOV: Horizontal field of view in degrees in the range [0,180]
*/
void	fill_camera(t_camera *cam, char **argv)
{
	cam->camera_pos = get_vector(*argv++);
	cam->rotation = get_vector(*argv++);
	cam->fov = get_scalar_size_t(*argv++);
	cam->focal_len = 1;
	cam->aspect_ratio = ASPECT_RATIO;
	cam->width = WINDOW_WIDTH;
	cam->max_bounces = MAX_BOUNCES;
}
