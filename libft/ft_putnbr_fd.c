/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:22:46 by ggasset-          #+#    #+#             */
/*   Updated: 2025/01/29 15:11:08 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//int main() {}

static void	print_0s(int fd, int count)
{
	while (count > 0)
	{
		write(fd, "0", 1);
		count--;
	}
}

static int	ft_destripate(int n, char *significant_digit, int *sig_magnit)
{
	int	i;

	i = 0;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		i++;
	}
	if (significant_digit)
		*significant_digit = ft_abs(n) + '0';
	if (sig_magnit)
		*sig_magnit = i;
	while (i)
	{
		n *= 10;
		i--;
	}
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		n2;
	int		tmp;
	int		sig_magnit;
	int		prev_magnit;
	char	c;

	write(fd, "0", !n);
	write(fd, "-", n < 0);
	sig_magnit = 0;
	prev_magnit = 0;
	n2 = n;
	while (n2)
	{
		tmp = ft_destripate(n2, &c, &sig_magnit);
		n2 -= tmp;
		if (prev_magnit)
			print_0s(fd, prev_magnit - sig_magnit - 1);
		write(fd, &c, 1);
		prev_magnit = sig_magnit;
	}
	print_0s(fd, sig_magnit * (n != 0));
}
