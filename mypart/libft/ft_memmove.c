/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:14:56 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/07 17:20:14 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*a;
	const unsigned char	*b;
	size_t				i;

	a = (unsigned char *)dest;
	b = (const unsigned char *)src;
	if (a > b && a < b + n)
	{
		i = n;
		while (i > 0)
		{
			i--;
			a[i] = b[i];
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
