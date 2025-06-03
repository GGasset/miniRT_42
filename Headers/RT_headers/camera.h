/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:50:09 by ggasset-          #+#    #+#             */
/*   Updated: 2025/06/02 22:06:50 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "objects.h"
# include "stdlib.h"
// # include "../minilibx_funcs.h"

typedef struct t_light
{
	t_point3	coords;
	double		brightness;
	t_color		color;
}		t_light;

typedef struct t_camera
{
	size_t		width;
	double		aspect_ratio;
	size_t		fov;
	size_t		max_bounces;
	t_point3	camera_pos;
	t_rotation	rotation;
}		t_camera;

typedef struct t_scene
{
	t_camera		camera;
	t_object_list	objects;
	t_light			ambient_light;
	t_light			light;
}		t_scene;

t_color	ray_color(t_ray ray, t_camera camera, t_object_list objs);
// int		render(t_render_data *render_data);

#endif
