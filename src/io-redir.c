/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io-redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 09:30:53 by moabed            #+#    #+#             */
/*   Updated: 2026/05/04 12:21:14 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

void	output_handle(t_redir *red, t_cmd **current_cmd, int option)
{
	int	fd;

	fd = -1;
	if (option == 1)
		fd = open(red->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (option == 2)
		fd = open(red->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		check_fds(*current_cmd);
		free_current_cmd(current_cmd);
		perror(red->filename);
	}
	else
	{
		if ((*current_cmd)->fd_out > 2)
			close((*current_cmd)->fd_out);
		(*current_cmd)->fd_out = fd;
	}
}

void	input_handle(t_redir *red, t_cmd **current_cmd)
{
	int	fd;

	fd = -1;
	if (access(red->filename, F_OK) == 0)
		fd = open(red->filename, O_RDONLY);
	if (fd == -1)
	{
		check_fds(*current_cmd);
		free_current_cmd(current_cmd);
		perror(red->filename);
	}
	else
	{
		if ((*current_cmd)->fd_in > 2)
			close((*current_cmd)->fd_in);
		(*current_cmd)->fd_in = fd;
	}
}
// wait for the expander
// void	heredoc(t_exec *shell,t_cmd *node)
// {
// 	int fd[2];

// 	if(pipe(fd) == -1)
// 	{
// 		ruin_everything(shell,1);
// 	}
// 	close(fd[1]);

// }

void	redir_handle(t_redir *redir, t_cmd **cmd)
{
	while (redir)
	{
		if (!*cmd)
			return ;
		if (redir->type == INPUT)
			input_handle(redir, cmd);
		else if (redir->type == TRUNC)
			output_handle(redir, cmd, 1);
		else if (redir->type == APPEND)
			output_handle(redir, cmd, 2);
		else if (redir->type == HEREDOC)
		{
			// heredoc(minishell);
		}
		redir = redir->next;
	}
}
