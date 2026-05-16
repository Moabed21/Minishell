/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:08:50 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 17:31:02 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sizecal(int n)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	ft_isnegative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static char	*flipper(char *ptr)
{
	int		x;
	int		i;
	char	temp;

	x = ft_strlen(ptr);
	i = 0;
	while (i < x / 2)
	{
		temp = ptr[i];
		ptr[i] = ptr[x - i - 1];
		ptr[x - i - 1] = temp;
		i++;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		isnegative;
	int		x;

	x = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	isnegative = ft_isnegative(n);
	if (isnegative)
		n *= -1;
	p = malloc(sizeof(char) * sizecal(n) + sizeof(char) * isnegative + 1);
	if (p == NULL)
		return (NULL);
	while (n)
	{
		p[x++] = (n % 10) + '0';
		n /= 10;
	}
	if (isnegative)
		p[x++] = '-';
	p[x] = '\0';
	return (flipper(p));
}

// #include <stdio.h>

// int	main(void){

// 	//char *p = ft_itoa(-2147483647);

// printf("%d",sizecal(-100));
// }