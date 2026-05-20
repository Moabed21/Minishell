/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:41:57 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 18:00:15 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(const char *sent, char c)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (sent[i])
	{
		while (sent[i] == c)
			i++;
		if (sent[i] != c && sent[i])
			counter++;
		while (sent[i] && sent[i] != c)
			i++;
	}
	return (counter);
}

static void	freefun(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	wordlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**splitted_arrf(char *sent, char sp, int wordscount,
		char **splitted_arr)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (j < wordscount)
	{
		while (sent[i] == sp)
			i++;
		len = wordlen(&sent[i], sp);
		splitted_arr[j] = ft_substr(sent, i, len);
		if (!splitted_arr[j])
		{
			freefun(splitted_arr);
			return (NULL);
		}
		i += len;
		j++;
	}
	splitted_arr[j] = NULL;
	return (splitted_arr);
}

char	**ft_split(const char *s, char c)
{
	int		wc;
	char	**splitted_arr;

	wc = countwords((char *)s, c);
	splitted_arr = malloc(sizeof(char *) * (wc + 1));
	return (splitted_arrf((char *)s, c, wc, splitted_arr));
}
// #include <stdio.h>

// int	main(void)
// {
// 	char x[] = "   the last wizard of all time ";
// 	printf("%d", countwords(x, ' '));
// }