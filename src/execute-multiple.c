/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:54:05 by moabed            #+#    #+#             */
/*   Updated: 2026/05/04 12:52:39 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

void    run_cmd(t_exec *shell, t_cmd *node)
{
    
}

void	multiple_cmds(t_exec *shell, t_cmd *cmds)
{
	int	prev_fd;

    ignore_signals();
	prev_fd = -1;
	while (cmds)
	{
		if (cmds->next)
			ft_fork_pipe(shell, cmds, 2);
		if (cmds->fork_id == -1)
			break ;
		prev_fd = shell->fd[1];
        close(shell->fd[0]);
		if (cmds->redir)
			redir_handle(cmds->redir, &cmds);
        if (!cmds)
            return;
        ft_fork_pipe(shell, cmds, 1);
        if (cmds->fork_id == -1)
			break ;
        if(cmds->fork_id == 0)
            run_cmd(shell,cmds);
		cmds = cmds->next;
	}
}

// TODO : recheck the fds closing if fork_id == -1
