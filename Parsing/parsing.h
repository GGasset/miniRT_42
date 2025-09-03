/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-03 14:44:19 by ggasset-          #+#    #+#             */
/*   Updated: 2025-09-03 14:44:19 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "camera.h"

int	expect_vec3(char *line, size_t *i, t_interval range);
int	expect_number(char *line, size_t *i, t_interval range, int expect_space);

#endif
