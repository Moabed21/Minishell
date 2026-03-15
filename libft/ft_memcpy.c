/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:52:14 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 21:08:45 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest1;
	const unsigned char	*src1;

	dest1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	while (n--)
	{
		*dest1++ = *src1++;
	}
	return (dest);
}

// #include <stdio.h>

// int	main(void){
//     char src[] = "zyxwvutsrqponmlkjihgfedcba";
//     char dst[20];
//     ft_memcpy(dst, src, 20);
//     printf("After ft_memcpy: \"%s\"\n", dst);
// }