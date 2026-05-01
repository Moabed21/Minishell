/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error-handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:19:58 by moabed            #+#    #+#             */
/*   Updated: 2026/05/01 12:46:43 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

void	error_display(int fd, char *cmd, char *right_end, t_exec *shell)
{
	int	cmdlen;
	int	rightlen;

	rightlen = ft_strlen(right_end);
	cmdlen = ft_strlen(cmd);
	write(fd, "minishell: ", 12);
	write(fd, cmd, cmdlen);
	write(fd, right_end, rightlen);
	write(fd, "\n", 1);
	shell->last_status = 2;
}

void	free_current_cmd(t_cmd **node)
{
	t_cmd	*ptr;
	t_redir *r;

	ptr = *node;
	(*node) = (*node)->next;
	free2d_array((*node)->args);
	while((*node)->redir)
	{
		r = (*node)->redir;
		r = r->next;
		free((*node)->redir);
	}
	free(ptr);
}

void	ruin_everything(t_exec *shell, int option)
{
	t_cmd *c;

	(void)option;
	c = shell->cmds;
	while (c)
	{
		c = c->next;
		free(shell->cmds);
		shell->cmds = c;
	}
	free(c);
}