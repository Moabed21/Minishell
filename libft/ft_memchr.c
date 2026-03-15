/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:08:45 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 17:14:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	v;

	p = (unsigned char *)s;
	v = (unsigned char)c;
	while (n--)
	{
		if (*p == v)
		{
			return (p);
		}
		p++;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 		char x[] ="ahmad";
// 		char *p;
// 		p = ft_memchr(x,'x',5);
// 		printf("%c %c %c",p[0], p[1],p[2]);
// }