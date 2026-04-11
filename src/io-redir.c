/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io-redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 09:30:53 by moabed            #+#    #+#             */
/*   Updated: 2026/04/11 17:32:09 by moabed           ###   ########.fr       */
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
		perror(red->filename);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	red->file_d = fd;
}

void	input_handle(t_redir *red, t_exec *minishell)
{
	int	fd;

	if (access(red->filename, F_OK) == 0)
		fd = open(red->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(red->filename);
		// exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	red->file_d = fd;
}

void	redir_handle(t_redir *redir, t_exec *minishell)
{
	while (redir)
	{
		if (redir->type == INPUT)
		{
			input_handle(redir, minishell);
		}
		else if (redir->type == TRUNC)
		{
			output_handle(redir, minishell);
		}
		else if (redir->type == APPEND)
		{
            
		}
		else if (redir->type == HEREDOC)
		{
		}
		redir = redir->next;
	}
}