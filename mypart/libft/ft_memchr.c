/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:15:11 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/09 11:56:01 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*a;
	size_t				i;

	i = 0;
	a = (const unsigned char *)s;
	while (i < n)
	{
		if (a[i] == (unsigned char)c)
		{
			return ((void *)a + i);
		}
		i++;
	}
	return (NULL);
}
/*
#include <string.h>

int main ()
{
	char	*b;
	char	*l;

	b = ft_memchr("ar\0r", '\0', 4);
	l = memchr("ar\0r", '\0',4);

	printf("%p\n%p", b, l);
} */