/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:26:56 by moabed            #+#    #+#             */
/*   Updated: 2025/08/19 21:05:23 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
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
// 	head = &n1;
// 	//printf("%d ",*(int *)head->next->next);
// }