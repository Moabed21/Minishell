/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:23:21 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 17:14:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	unsigned char		x;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (s == d || n == 0)
		return (dest);
	if (d > s && d < s + n)
	{
		x = *s;
		d += --n;
		s += n;
		while (n--)
		{
			*d-- = *s--;
		}
		*d = x;
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

// #include <stdio.h>

// int	main(void){
// 	char	src[] = "lorem ipsum dolor sit amet";
// 	char *dest;

// 	dest = src+1;
// ft_memmove(dest, src, 8);
// printf("%s",dest);
// }