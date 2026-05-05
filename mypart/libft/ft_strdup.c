/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:01:21 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/23 18:58:47 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t			n;
	int				i;
	unsigned char	*str;

	i = 0;
	n = ft_strlen(s);
	str = (unsigned char *)malloc(n + 1);
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return ((char *)str);
}

/* int	main(void)
{
	const char *s = NULL;
	printf("%s\n", ft_strdup(s));
}  */