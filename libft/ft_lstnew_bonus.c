/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:46:50 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 21:05:16 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*p;

	p = malloc(sizeof(t_list));
	if (!(p))
		return (NULL);
	p->content = content;
	p->next = NULL;
	return (p);
}

// #include <stdio.h>

// int	main(void)
// {
// t_list n1, n2, n3;//, *head;
//  int	a = 42,	*x = &a;
// n1.content = (int *)x;
// n1.next = &n2;
// n2.content = (int *)20;
// n2.next = &n3;
// n3.content = (int *)10;
// n3.next = NULL;
// head =&n1;
// t_list *p;
// p = ft_lstnew(x);
// printf(" %d ", *(int *)p->content);
// }