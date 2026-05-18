/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:40:51 by samarnah          #+#    #+#             */
/*   Updated: 2026/05/18 15:10:45 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"

static int	is_op_type(t_token_type type)
{
	return (type == PIPE || type == INPUT || type == TRUNC || type == APPEND
		|| type == HEREDOC);
}

static int	check_pipe_error(t_token *tmp)
{
	if (!tmp->next || tmp->next->type == END || tmp->next->type == PIPE)
	{
		errmsg("syntax error near unexpected token", tmp->value, 1);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_redir_error(t_token *tmp)
{
	if (!tmp->next || tmp->next->type == END)
	{
		errmsg("syntax error near unexpected token", "newline", 1);
		return (FAILURE);
	}
	if (tmp -> type == HEREDOC && tmp->next->type == INPUT)
	{
		errmsg("syntax error near unexpected token", "newline", 1);
		return (FAILURE);
	}
	if (is_op_type(tmp->next->type))
	{
		errmsg("syntax error near unexpected token", tmp->next->value, 1);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_consecutives(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	if (!tmp)
		return (SUCCESS);
	if (tmp->type == PIPE)
		return (errmsg("syntax error near unexpected token",
				tmp->value, 1), FAILURE);
	while (tmp && tmp->type != END)
	{
		if (tmp->type == PIPE && check_pipe_error(tmp) == FAILURE)
			return (FAILURE);
		if (is_redir(tmp->type) && check_redir_error(tmp) == FAILURE)
			return (FAILURE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
