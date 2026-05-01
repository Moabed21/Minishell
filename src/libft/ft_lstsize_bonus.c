/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:27:33 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 21:05:12 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*p;

	if (lst == NULL)
		return (0);
	if (lst->content == NULL)
		return (0);
	p = lst;
	counter = 1;
	while (p->next)
	{
		p->next = p->next->next;
		counter++;
	}
	return (counter);
}
// #include <stdio.h>

// int	main(void)
// {
// 	t_list n1, n2, n3, *head;
// 	int a = 42, *x = &a;
// 	n1.content = (int *)x;
// 	n1.next = &n2;
// 	n2.content = (int *)20;
// 	n2.next = &n3;
// 	n3.content = (int *)10;
// 	n3.next = NULL;
// 	head ;
// 	printf("%d ",ft_lstsize(head));
// }