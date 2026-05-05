/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shathaamarnah <shathaamarnah@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:21:56 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/04 14:57:13 by shathaamarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*cmd_new(void)
{
    t_cmd   *new_cmd;
    
    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return NULL;
    new_cmd->args = NULL;
    new_cmd->redir = NULL;
    new_cmd->next = NULL;
    return (new_cmd);
}

void	cmd_addback(t_cmd **list, t_cmd *new_node)
{
	t_cmd	*tmp;

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

t_token	*next_command(t_token *tokens)
{
	while (tokens && tokens->type != PIPE && tokens->type != END)
		tokens = tokens->next;
	if (tokens && tokens->type == PIPE)
		return (tokens->next);
	return (NULL);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_args(cmds->args);
		free_redirs(cmds->redir);
		free(cmds);
		cmds = tmp;
	}
}

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