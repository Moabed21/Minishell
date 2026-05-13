/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error-handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:19:58 by moabed            #+#    #+#             */
/*   Updated: 2026/05/09 20:19:45 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

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
		// to be checked
		// free(r->filename);
		free(r);
		r = tmp;
	}
	free(ptr);
}

void	ruin_everything(t_exec *shell)
{
	if (shell->first_env_node)
		env_ruin(&shell->first_env_node);
	if (shell->cmds)
	{
		free_cmds_list(&shell->cmds);
		shell->cmds = NULL;
	}
}

void	free_cmds_list(t_cmd **cmds)
{
	t_cmd	*curr;
	t_cmd	*next;

	if (!cmds || !*cmds)
		return ;
	curr = *cmds;
	while (curr)
	{
		next = curr->next;
		free_current_cmd(&curr);
		curr = next;
	}
	*cmds = NULL;
}

void	errmsg(char *errmsg, char *detail, int check)
{
	char	*msg;
	char	*tmp;

	msg = ft_strdup("minishell: ");
	tmp = msg;
	msg = ft_strjoin(msg, errmsg);
	free(tmp);
	tmp = msg;
	if (check)
		msg = ft_strjoin(msg, " `");
	else
		msg = ft_strjoin(msg, ": ");
	free(tmp);
	tmp = msg;
	msg = ft_strjoin(msg, detail);
	free(tmp);
	if (check)
	{
		tmp = msg;
		msg = ft_strjoin(msg, "'");
		free(tmp);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr((void **)&msg);
}
