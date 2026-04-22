/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shathaamarnah <shathaamarnah@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:55:39 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/04/20 19:01:15 by shathaamarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//the output of this code is your input to the execution

t_cmd	*prepare_for_execution(char *input, char **env, int last_status)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenization(input);
	if (!tokens)
		return (NULL);
	if (check_consecutives(&tokens) == FAILURE)
	{
		tokenlistclear(&tokens);
		return (NULL);
	}
	if (expand_tokens(tokens, env, last_status) == FAILURE)
	{
		tokenlistclear(&tokens);
		return (NULL);
	}
	cmds = parsing(tokens);
	tokenlistclear(&tokens);
	return (cmds);
}
