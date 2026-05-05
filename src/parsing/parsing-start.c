/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:55:39 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/05 16:50:17 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"

t_cmd	*prepare_for_execution(char *input, char **env, int last_status)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenization(input);
	if (!tokens)
		return (NULL);
	if (check_if_var(&tokens) == FAILURE)
	{
		tokenlistclear(&tokens);
		return (NULL);
	}
    if (!expand_tokens(&tokens, env, last_status))	
    {
		tokenlistclear(&tokens);
		return (NULL);
	}
	cmds = parsing(tokens);
	tokenlistclear(&tokens);
	return (cmds);
}
