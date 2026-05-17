/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 06:03:41 by moabed            #+#    #+#             */
/*   Updated: 2026/05/17 23:43:38 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executionpart.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	init_vals(t_exec *shell, t_cmd *cmds)
{
	shell->cmds_count = 0;
	while (cmds)
	{
		check_cmds(cmds);
		cmds->fd_in = 0;
		cmds->fd_out = 1;
		cmds->fork_id = 0;
		shell->cmds_count++;
		cmds = cmds->next;
	}
}

int	preprocess_heredocs(t_exec *shell, t_cmd *cmds)
{
	t_redir	*redir;

	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			if (redir->type == HEREDOC && heredoc(shell, redir->filename, &cmds,
					redir->quoted) == -1)
			{
				shell->last_status = 130;
				return (-1);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
