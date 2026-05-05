/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:04:20 by samarnah          #+#    #+#             */
/*   Updated: 2025/08/23 19:15:35 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c > 64 && c < 91)
		return (1);
	else
		return (0);
}
/* #include <stdio.h>
int main ()
{
	printf("%d\n", ft_isalpha(1024));
} */