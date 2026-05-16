/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:11:43 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 19:52:17 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	char	*ptp;
	size_t	i;

	if (!(s))
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	s += start;
	p = malloc(sizeof(char) * len + 1);
	if (!(p))
		return (p);
	ptp = p;
	while (i < len && *s)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (ptp);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	x[] = "lorem ipsum dolor sit amet";
// 	char	*p;

// 	p = ft_substr(x, 0, 10);
// 	printf("%s", p);
// 	free(p);
// }
