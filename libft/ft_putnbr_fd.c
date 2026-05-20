/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:57:26 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 17:14:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	x;

	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	else if (nb < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(nb *= -1, fd);
	}
	else if (nb <= 9)
	{
		x = nb + '0';
		write(fd, &x, 1);
		return ;
	}
	else if (nb > 9)
	{
		x = (nb % 10) + '0';
		ft_putnbr_fd(nb /= 10, fd);
		write(fd, &x, 1);
	}
}

// int	main(void)
// {
// 	ft_putnbr_fd(-987441, 2);
// }
