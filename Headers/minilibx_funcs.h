/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_funcs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 16:02:48 by ggasset-          #+#    #+#             */
/*   Updated: 2025-05-22 16:02:48 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_FUNCS_H
# define MINILIBX_FUNCS_H

# include "mlx.h"
# include "camera.h"

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 300
# endif
# ifndef RENDER_WIDTH
	#define RENDER_WIDTH WINDOW_WIDTH
#endif
# ifndef ASPECT_RATIO
// 16:9 default aspect ratio
#  define ASPECT_RATIO 1.77777
# endif
# ifndef MAX_BOUNCES
#  define MAX_BOUNCES 3
# endif

typedef struct s_res
{
	int	x;
	int	y;
}			t_res;

typedef struct s_win_d
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_res	res;
}				t_win_d;

typedef struct t_render_data
{
	t_scene	scene;
	t_win_d	img;
	void	*mlx;
	void	*win;
}		t_render_data;


int		render_image(t_render_data *render_d);
void	render_loop(t_render_data *render_d);

int		free_img(t_render_data *d);
// Does not free scene
void	free_render_data(t_render_data *d);

#endif
