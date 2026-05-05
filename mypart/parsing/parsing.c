/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shathaamarnah <shathaamarnah@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:19:39 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/04 15:03:44 by shathaamarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
