/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:40:27 by samarnah          #+#    #+#             */
/*   Updated: 2026/05/13 19:40:29 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

t_cmd	*parsing(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*new_cmd;

	cmds = NULL;
	while (tokens && tokens->type != END)
	{
		new_cmd = cmd_new();
		if (!new_cmd)
			return (free_cmds(cmds), NULL);
		new_cmd->args = fill_args(tokens);
		if (!new_cmd->args)
			return (free_cmds(cmds), NULL);
		if (!parse_redirs(new_cmd, tokens))
			return (free_cmds(cmds), NULL);
		cmd_addback(&cmds, new_cmd);
		tokens = next_command(tokens);
	}
	return (cmds);
}
