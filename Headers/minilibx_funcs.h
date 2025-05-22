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

typedef struct t_render_data
{
}		t_render_data;

#endif
