/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:32:04 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/23 21:02:34 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	s;

	i = 0;
	n = 1;
	s = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\r'
		|| nptr[i] == '\n' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n = n * -1;
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		s = (s * 10) + (nptr[i] - '0');
		i++;
	}
	return (s * n);
}

/* int main()
{
	printf("%d\n", ft_atoi(""));
} */
