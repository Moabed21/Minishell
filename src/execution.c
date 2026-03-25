/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/03/24 18:05:25 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void	output_handle(t_redir *red, t_exec *minishell)
{
	int	fd;

	fd = -1;
	fd = open(red->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		// close(fds[0]);
		// close(fds[1]);
		// perror(red->filename);
		// exit(EXIT_FAILURE);
	}
	red->file_d = fd;
}
void	input_handle(t_redir *red, t_exec *minishell)
{
	int	fd;

	if (access(red->filename, F_OK) == 0)
		fd = open(red->filename, O_RDONLY);
	if (fd == -1)
	{
		// ruin_everything(cmds_list);
	}
	red->file_d = fd;
}
void	redir_handle(t_redir *redir, t_exec *minishell)
{
	while(redir)
	{
		if (redir->type == INPUT)
		{
			input_handle(redir, minishell);
		}
		if (redir->type == TRUNC)
		{
			output_handle(redir,minishell);
		}
		redir = redir->next;
	}
}

void	execute_one_cmd(t_exec *minishell)
{
	// before executing check if there is a redir
	minishell->cmds->fork_id = fork();
	if (minishell->cmds->fork_id == -1)
	{
		
	}
	if (minishell->cmds->redir != NULL)
	{
		redir_handle(minishell->cmds->redir, minishell);
	}
}
void	ruin_everything(t_cmd *cmds_list)
{
}
void	multiple_cmds(t_cmd *cmds_list)
{
	if (pipe(cmds_list->fd) == -1)
		ruin_everything(cmds_list);
	cmds_list->fork_id = fork();
	if (cmds_list->fork_id == -1)
	{
		ruin_everything(cmds_list);
	}
}

void	execution(t_exec *minishell, char **envp)
{
	t_env	*env;

	env = env_init(envp);
	minishell->first_env_node = env;
	// here is the execution tree root
	if (!minishell->cmds->next)
		execute_one_cmd(minishell);
	else
		multiple_cmds(minishell);
	// case 1) having only one command
	// case 2) having one with redir
	// case 3) having 2 cmds (without redirs)
	// case 4) having 2 with redirs
	// the main behavior is to look if there is redirs then execute the command,
	// if there is , execute it then look for the second command if existed
}
