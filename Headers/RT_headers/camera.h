/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:50:09 by ggasset-          #+#    #+#             */
/*   Updated: 2025/07/23 18:31:57 by alvmoral         ###   ########.fr       */
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
	size_t		height;
	size_t		aspect_ratio;
	size_t		fov;
	size_t		max_bounces;
	t_data		focal_len;
	t_point3	camera_pos;
	t_rotation	rotation;
}		t_camera;

t_color	point_iluminate(t_color current, t_hit_info info, t_light light);
t_color	iluminate(t_color current, t_color object_color, t_light light);
t_color	shift(t_color old, t_color target, t_data factor, float reflects);
t_color	get_sky_color(t_camera camera, size_t pixel_y);

typedef struct t_scene
{
	t_camera		camera;
	t_object_list	objects;
	t_light			ambient_light;
	t_light			light;
}		t_scene;

t_ray	create_ray(t_camera camera, size_t pixel_i);
// int		render(t_render_data *render_data);

void			print_t_scene(t_scene s);
char			**format_line(char *line);
unsigned int	ft_atoui(const char *str);
t_data			get_scalar(char *value);
size_t			get_scalar_size_t(char *value);
t_vec3			get_vector(char *dim);


void	fill_ambient_ligth(t_light *ambient, char **argv);
void	fill_ligth(t_light *light, char **argv);
void	fill_camera(t_camera *cam, char **argv);
void	fill_obj(t_object *obj, char **argv);
void	fill_obj_list(t_object_list *objs, char **argv);

#endif
