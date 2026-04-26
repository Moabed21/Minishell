/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:45:49 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/04/26 13:49:48 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	variable_check(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->value[i])
	{
		if ((*token_node)->value[i] == '$')
		{	
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
			// if the previous token is a heredoc (<<), the shell doesn't expand variables so it stops checking
				break ;
			(*token_node)->type = VAR;
			return ;
		}
		i++;
	}
}

int	check_if_var(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	// if the first token is a pipe
	if (tmp->type == PIPE)
	{
		errmsg("syntax error near unexpected token", tmp->value, 1);
		return (0);
	}
	while (tmp)
	{
		variable_check(&tmp); // if the token contains $, its type becomes VAR
		if (check_consecutives(&tmp) == 1)
			return (FAILURE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
