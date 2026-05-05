/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:34:07 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/24 14:29:26 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, const char *set)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (c == set[j])
			return (1);
		j++;
	}
	return (0);
}

static char	*ft_aftrim1(const char *s1, const char *set)
{
	int		i;
	size_t	len;
	size_t	k;
	char	*aftrim1;

	i = 0;
	k = 0;
	while (s1[i] && isinset(s1[i], set))
		i++;
	len = ft_strlen(s1) - i;
	aftrim1 = malloc(len + 1);
	if (!aftrim1)
		return (NULL);
	while (s1[i] != '\0')
	{
		aftrim1[k] = s1[i];
		k++;
		i++;
	}
	aftrim1[k] = '\0';
	return (aftrim1);
}

static char	*ft_aftrim2(const char *s1, const char *set)
{
	char	*aftrim2;
	char	*aftrim1;
	size_t	j;

	aftrim1 = ft_aftrim1(s1, set);
	if (!aftrim1)
		return (NULL);
	j = ft_strlen(aftrim1);
	while (j > 0 && isinset(aftrim1[j - 1], set))
		j--;
	aftrim2 = malloc(j + 1);
	if (!aftrim2)
	{
		free(aftrim1);
		return (NULL);
	}
	ft_strlcpy(aftrim2, aftrim1, j + 1);
	free(aftrim1);
	return (aftrim2);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*finaltrim;

	if (!s1 || !set)
		return (NULL);
	finaltrim = ft_aftrim2(s1, set);
	return (finaltrim);
}

/* int	main(void)
{
	char *s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n T ";
	char *set = " \n\t";
	printf("%s\n", ft_strtrim(s1, set));
} */
/* int	main(void)
{
	char *s1 = "+ +--+mohammedsljf  s+--hel+lo+-";
	char *set = "+- ";
	printf("%s\n", ft_strtrim(s1, set));
} */