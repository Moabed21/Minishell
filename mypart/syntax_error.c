/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shathaamarnah <shathaamarnah@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:51:39 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/04/22 18:25:13 by shathaamarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	consecutive_ops(t_token *token_node)
{
	if (token_node->prev)
	{
	    // two pipes in a row
		if (token_node->type == PIPE && token_node->prev->type == PIPE) 
			return (FAILURE);
		// two redir in a row
		if (token_node->type > PIPE && token_node->prev->type > PIPE) 
			return (FAILURE);
		// when the command ends with a pipe or redirection
		if (token_node->type == END && token_node->prev->type >= PIPE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	check_consecutives(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	if (tmp && tmp->type == PIPE)
	{
		errmsg("syntax error near unexpected token", tmp->value, 1);
		return (FAILURE);
	}
	while (tmp)
	{
		if (consecutive_ops(tmp) == FAILURE)
		{
			if (tmp->type == END && tmp->prev && tmp->prev->type > PIPE) // redirection at end
				errmsg("syntax error near unexpected token", "newline", 1);
			else if (tmp->type == END && tmp->prev) // pipe at end
				errmsg("syntax error near unexpected token",tmp->prev->value, 1);
			else
				errmsg("syntax error near unexpected token", tmp->value, 1); // multiple operators
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
