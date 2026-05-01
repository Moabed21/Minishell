/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:08:26 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 17:14:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*totalsize;
	char	*ptr;

	totalsize = malloc((ft_strlen(s2) + ft_strlen(s1) + 1) * sizeof(char));
	ptr = totalsize;
	if (totalsize == NULL)
		return (NULL);
	while (*s1)
	{
		*totalsize++ = *s1++;
	}
	while (*s2)
	{
		*totalsize++ = *s2++;
	}
	*totalsize = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int	main(void){
char	x1[] = "the ";
char	x2[] = "last";
char	*p = ft_strjoin(x1,x2);
		printf("%s",p);
}*/