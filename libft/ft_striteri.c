/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:10:53 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 18:00:18 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
// if you write it in the loop f(i , &s[i]) its wrong cuz i need the
// address of the current index
// int	main(void)
// {
// 	char p[] = "LoReM iPsUm";
// 	ft_striteri(p,f);
// }
// #include <stdio.h>
// void	f(unsigned int i, char p[i])
// {
// 	if(p[i] >= 65 && p[i] <= 90)
// 		p[i] += 32;
// 	else if(p[i] >= 97 && p[i] <= 122)
// 		p[i] -= 32;
// }