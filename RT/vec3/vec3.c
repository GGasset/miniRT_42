/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:08:22 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 17:08:48 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3(t_data x, t_data y, t_data z)
{
	t_vec3	vec;

	vec.vs[0] = x;
	vec.vs[1] = y;
	vec.vs[2] = z;
	return (vec);
}

void	asign_vec3(t_vec3 *vec, t_data x, t_data y, t_data z)
{
	vec->vs[0] = x;
	vec->vs[1] = y;
	vec->vs[2] = z;
}

void	copy_vec3(t_vec3 *dest, t_vec3 src)
{
	dest->vs[0] = x(src);
	dest->vs[1] = y(src);
	dest->vs[2] = z(src);
}

/*
 * Evalúa: V op V op V ... (n_ops operandos → n_ops-1 operadores)
 * Ej.: ft_vecop(3, v1, '+', v2, '-', ft_vecop(2, v3, '*', v4))
 *
 * Reglas:
 *  - Evaluación estrictamente izquierda→derecha (sin precedencia).
 *  - Operadores soportados: '+', '-', '*'
 *  - '*' es multiplicación componente a componente.
 *  - Para “paréntesis” usa llamadas anidadas a ft_vecop (devuelven t_vec3).
 */
t_vec3	ft_vecop(int n_ops, ...)
{
	va_list	ap;
	t_vec3	ret;
	t_vec3	acc;
	int		op;
	t_vec3	rhs;

	if (n_ops <= 0)
		return (ft_bzero(ret.vs, 3 * sizeof(t_data)), ret);
	va_start(ap, n_ops);
	acc = va_arg(ap, t_vec3);
	while (n_ops--)
	{
		op = va_arg(ap, int);
		rhs = va_arg(ap, t_vec3);
		if (op == '+')
			acc = vec_sum(acc, rhs);
		else if (op == '-')
			acc = vec_sust(acc, rhs);
	}
	va_end(ap);
	return (acc);
}
