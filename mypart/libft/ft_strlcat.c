/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:05:34 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/23 19:47:40 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	n;

	j = 0;
	i = 0;
	while (dst[i] != '\0')
		i++;
	if (ft_strlen(dst) > size)
		n = ft_strlen(src) + size;
	else
		n = ft_strlen(dst) + ft_strlen(src);
	if (size > 0)
	{
		while (src[j] != '\0' && (i + j) < size - 1)
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
		while (src[j] != '\0')
			j++;
	}
	return (n);
}
/*
 #include <string.h>
int main ()
{
    char dst[] = "HEllo";
    const char src[10] = "abcdef";
    size_t size;
    printf("%d\n", ft_strlcat(dst, src, 3));
    printf("%s\n", dst);
} */
