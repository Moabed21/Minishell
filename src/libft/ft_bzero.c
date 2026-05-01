/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:36:50 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 17:14:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n--)
	{
		*(unsigned char *)s = 0;
		s++;
	}
}
/*
#include <stdio.h>

int	main(void){
	char y[]="1234";

	ft_bzero(y,2);
printf("%c",y[0]);
printf("%c",y[1]);
printf("%c",y[2]);
printf("%c",y[3]);
printf("%c",y[4]);
}*/