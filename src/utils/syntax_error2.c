/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:55:10 by samarnah          #+#    #+#             */
/*   Updated: 2026/05/13 18:55:22 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"

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
