/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:24:11 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/23 20:57:13 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			n;
	size_t			i;
	unsigned char	*substr;

	n = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	if (start >= n || len == 0)
		return (ft_strdup(""));
	if (n > len + start)
		substr = malloc(len + 1);
	else
		substr = malloc((n - start) + 1);
	if (!substr)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return ((char *)substr);
}
/*
int	main(void)
{
	char const	*s = "shatha hello";
	unsigned int	start = 12;
	size_t	len = 7;
	printf("%s\n", ft_substr(s, start, len));
} */