/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:26:20 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 18:00:37 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstsize;
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	dstsize = ft_strlen(dst);
	if (size == 0)
		return (srcsize);
	if (dstsize >= size)
		return (size + srcsize);
	i = 0;
	while (src[i] && (dstsize + i) < (size - 1))
	{
		dst[dstsize + i] = src[i];
		i++;
	}
	dst[dstsize + i] = '\0';
	return (dstsize + srcsize);
}
/*
size is the expected size of the dst we have sent , in reality ,
	if its lower or equal than dstsize
(dstsize > size) we should return the expected string (srclen +size) but,
	if its higher than the dst size
just return the (dstsize + srcsize)
*/