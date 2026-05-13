/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inserting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:39:45 by samarnah          #+#    #+#             */
/*   Updated: 2026/05/13 19:39:48 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"

char	*append_char(char *s, char c)
{
	char	*new;
	int		len;
	int		i;

	len = 0;
	if (s)
		len = ft_strlen(s);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(s);
	return (new);
}

t_token	*create_tokens_from_words(char **words)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;
	while (words[i])
	{
		token_addback(&list, token_new(words[i], WORD));
		i++;
	}
	return (list);
}

static void	replace_inthemiddle(t_token *to_del, t_token *tmp, t_token *insert)
{
	t_token	*last;

	while (tmp != to_del)
		tmp = tmp->next;
	insert->prev = tmp->prev;
	tmp->prev->next = insert;
	last = insert;
	while (last->next)
		last = last->next;
	if (tmp->next)
		tmp->next->prev = last;
	last->next = tmp->next;
}

t_token	*insert_list(t_token **head, t_token *to_del, t_token *insert)
{
	t_token	*tmp;
	t_token	*last;

	tmp = *head;
	if (tmp == NULL)
		*head = insert;
	else if (tmp == to_del)
	{
		*head = insert;
		insert->prev = NULL;
		last = insert;
		while (last->next)
			last = last->next;
		last->next = tmp->next;
		if (tmp->next != NULL)
			tmp->next->prev = last;
	}
	else
		replace_inthemiddle(to_del, tmp, insert);
	free_ptr((void **)&to_del->value);
	free_ptr((void **)&to_del);
	return (insert);
}
