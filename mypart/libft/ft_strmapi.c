/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:59:14 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/23 20:11:17 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	l;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	l = ft_strlen(s);
	result = malloc(l + 1);
	if (!result)
		return (NULL);
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[l] = '\0';
	return (result);
}
/* char ft_touper(unsigned int c, char x)
{
	(void) c;
	if (x > 96 && x < 123)
		return (x - 32);
	else
		return (x);
}
int main ()
{
		char  *s = "shatha";
	printf("%s\n", ft_strmapi(s, ft_touper));
} */