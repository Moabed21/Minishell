/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:26:51 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 17:14:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int x)
{
	int	i;

	i = 0;
	if (x < 127 && x >= 32)
		i = 1;
	else
	{
		i = 0;
	}
	return (i);
}
/*
int	main(void){

char test[]= "Zf09";
int i= ft_str_is_printable(test);
char	x;
x = i+ '0';
write(1,&x,1);
}*/
