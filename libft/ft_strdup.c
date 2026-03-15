/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:47:19 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 18:16:09 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		length;

	length = ft_strlen(src);
	dest = malloc(sizeof(char) * length + 1);
	if (!(dest))
		return (NULL);
	ft_strcpy(dest, (char *)src);
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// char	*x = "lorem ipsum dolor sit amet";
// char *s = ft_strdup(x);
// printf("%s\n",s);
// free(s);
// }
