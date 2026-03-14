/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shathaamarnah <shathaamarnah@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:57:34 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/03/14 16:35:43 by shathaamarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *token_new(char *value, t_token_type type)
{
    t_token *node;

    node = malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    node->value = value;
    node->type = type;
    node->prev = NULL;
    node->next = NULL;
    return (node);
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
