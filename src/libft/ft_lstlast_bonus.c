/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 02:12:08 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 21:05:18 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptrlast;

	if (!lst)
		return (NULL);
	ptrlast = lst;
	while (ptrlast->next)
	{
		ptrlast = ptrlast->next;
	}
	return (ptrlast);
}
