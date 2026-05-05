/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shathaamarnah <shathaamarnah@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:51:39 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/04 15:11:25 by shathaamarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_operator(t_token_type type)
{
	return (type == PIPE || type == INPUT || type == TRUNC
		|| type == APPEND || type == HEREDOC);
}

static int	consecutive_ops(t_token *token_node)
{
	if (token_node->prev)
	{
	    // two pipes in a row
		if (token_node->type == PIPE && token_node->prev->type == PIPE) 
			return (FAILURE);
		// two redir in a row
		if (is_redir(token_node->type) && is_redir(token_node->prev->type))
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
	if (!tmp)
		return (SUCCESS);
	if (tmp->type == PIPE)
	{
		errmsg("syntax error near unexpected token", tmp->value, 1);
		return (FAILURE);
	}
	while (tmp && tmp->type != END)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next || tmp->next->type == END || tmp->next->type == PIPE)
			{
				errmsg("syntax error near unexpected token", tmp->value, 1);
				return (FAILURE);
			}
		}
		else if (is_redir(tmp->type))
		{
			if (!tmp->next || tmp->next->type == END)
			{
				errmsg("syntax error near unexpected token", "newline", 1);
				return (FAILURE);
			}
			if (is_operator(tmp->next->type))
			{
				errmsg("syntax error near unexpected token", tmp->next->value, 1);
				return (FAILURE);
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void	variable_check(t_token *token_node)
{
	int	i;

	if (!token_node || !token_node->value)
		return ;
	i = 0;
	while (token_node->value[i])
	{
		if (token_node->value[i] == '$')
		{
			if (token_node->prev && token_node->prev->type == HEREDOC)
				return ;
			token_node->type = VAR;
			return ;
		}
		i++;
	}
}

int	check_if_var(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	while (tmp)
	{
		variable_check(tmp);
		tmp = tmp->next;
	}
	return (check_consecutives(token_lst));
}
