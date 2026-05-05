/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:10:40 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/23 19:10:57 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counting(long n)
{
	int	count;

	if (n <= 0)
		count = 1;
	else
		count = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	x;
	char	*digits;
	int		i;
	int		len;

	x = n;
	len = counting(x);
	i = len - 1;
	digits = malloc(len + 1);
	if (!digits)
		return (NULL);
	digits[len] = '\0';
	if (x == 0)
		digits[0] = '0';
	if (x < 0)
	{
		x = -x;
		digits[0] = '-';
	}
	while (x > 0)
	{
		digits[i--] = (char)('0' + x % 10);
		x /= 10;
	}
	return (digits);
}
/* 
int main () {
	printf("%s\n", ft_itoa(-894463));
	return (0);
} */