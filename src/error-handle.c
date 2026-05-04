/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error-handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:19:58 by moabed            #+#    #+#             */
/*   Updated: 2026/05/03 19:24:23 by moabed           ###   ########.fr       */
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
	t_redir	*r;
	t_redir	*tmp;

	if (!node || !*node)
		return ;
	check_fds(*node);
	ptr = *node;
	*node = NULL;
	free2d_array(ptr->args);
	r = ptr->redir;
	while (r)
	{
		tmp = r->next;
		free(r->filename);
		free(r);
		r = tmp;
	}
	free(ptr);
}

void	ruin_everything(t_exec *shell)
{
	t_cmd *tmp;

	env_ruin(&shell->first_env_node);
	if (!shell->cmds)
		return ;
	while (shell->cmds)
	{
		tmp = shell->cmds->next;
		shell->cmds->next = NULL;
		free_current_cmd(&shell->cmds);
		shell->cmds = tmp;
	}
}