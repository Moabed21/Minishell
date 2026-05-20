/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:52:14 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 17:14:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	v;

	p = (unsigned char *)s;
	v = (unsigned char)c;
	while (n--)
	{
		*p = v;
		p++;
	}
	return (s);
}
/*
#include <stdio.h>

int	main(void){
	int x[4];
ft_memset(x,'a',sizeof(x));
printf("%c",x[0]);
printf("%c",x[1]);
printf("%c",x[2]);
printf("%c",x[3]);
printf("%c",x[4]);
}*/