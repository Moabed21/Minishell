/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 00:26:16 by moabed            #+#    #+#             */
/*   Updated: 2025/08/17 17:39:05 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	left;
	size_t	right;

	if (!(s1))
		return (NULL);
	if (!(set))
		return (ft_strdup(s1));
	right = ft_strlen(s1) - 1;
	left = 0;
	while (s1[left] && ft_strchr(set, s1[left]))
		left++;
	while (s1[right] && ft_strchr(set, s1[right]))
		right--;
	return (ft_substr(s1, left, right - left + 1));
}

// #include <stdio.h>

// int	main(void)
// {
// 	char x[] = "the last wizard ";
// 	char y[] = "the";

// 	char *p = ft_strtrim(x, y);
// 	printf("%s", p);
// 	free(p);
// }