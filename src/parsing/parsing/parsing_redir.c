/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:22:27 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/05 16:44:47 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"

t_redir	*redir_new(t_token_type type, char *filename, int quoted)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	redir->quoted = quoted;
	redir->next = NULL;
	return (redir);
}

void	redir_addback(t_redir **list, t_redir *new_node)
{
	t_redir	*tmp;

	if (!new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

int	parse_redirs(t_cmd *cmd, t_token *tokens)
{
	t_redir	*redir;

	while (tokens && tokens->type != PIPE && tokens->type != END)
	{
		if (is_redir(tokens->type))
		{
			if (!tokens->next || !tokens->next->value)
				return (0);
			redir = redir_new(tokens->type, tokens->next->value, tokens->next->quoted);
			if (!redir)
				return (0);
			redir_addback(&cmd->redir, redir);
			tokens = tokens->next->next;
		}
		else
			tokens = tokens->next;
	}
	return (1);
}

int	is_redir(t_token_type type)
{
	return (type == INPUT || type == TRUNC
		|| type == APPEND || type == HEREDOC);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}