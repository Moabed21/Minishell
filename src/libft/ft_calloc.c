/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:50:37 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 21:06:43 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
	if (p == NULL)
	{
		return (p);
	}
	return (ft_memset(p, 0, nmemb * size));
}
/*
#include <stdio.h>

int	main(void){
		int *p = ft_calloc(20,4);
		for(int i =0; i < 20; i++)
		{
				printf("%d   ",p[i]);
		}
}*/