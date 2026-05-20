/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:39:04 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 18:55:30 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*v;

	p = (unsigned char *)s1;
	v = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*p - *v != 0)
			return (*p - *v);
		p++;
		v++;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// int	x = ft_memcmp("abcdefghij", "abcdefgxyz", 7);
// printf("%d",x);

// }