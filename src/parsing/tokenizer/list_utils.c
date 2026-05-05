/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:57:34 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/05 16:45:04 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/parsingpart.h"

t_token	*token_new(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->quoted = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void token_addback(t_token **list, t_token *new_node)
{
    t_token *tmp;

    if (!list || !new_node)
        return;
    if (*list == NULL)
    {
        *list = new_node;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
    new_node->prev = tmp;
}

void tokenlistclear(t_token **list)
{
    t_token *tmp;
    t_token *next;

    if (!list || !*list)
        return;
    tmp = *list;
    while (tmp)
    {
        next = tmp->next;
        free(tmp->value);
        free(tmp);
        tmp = next;
    }
    *list = NULL;
}

void del_one(t_token *node)
{
    if (!node)
        return;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node->value);
    free(node);
}

void free_ptr(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}
