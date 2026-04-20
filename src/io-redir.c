/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io-redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 09:30:53 by moabed            #+#    #+#             */
/*   Updated: 2026/04/20 12:20:25 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void	output_handle(t_redir *red, t_exec *minishell,t_cmd **cmd, int option)
{
	int	fd;

	fd = -1;
	if(option == 1)
		fd = open(red->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if(option == 2)
		fd = open(red->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		free_current_cmd(cmd);
		perror(red->filename);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	input_handle(t_redir *red, t_exec *minishell,t_cmd **current_cmd)
{
	int	fd;

	fd = -1;
	if (access(red->filename, F_OK) == 0)
		fd = open(red->filename, O_RDONLY);
	if (fd == -1)
	{
		free_current_cmd(current_cmd);
		perror(red->filename);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}
//wait for the expander
void	heredoc(t_exec *minishell)
{
	// char *s;
	// int delimeter_len;
	
	// delimeter_len = ft_strlen(minishell->cmds->args[0]);
	while(1)
	{
		// read(0,s,100000);
		
		
			
		
	}
	
}

void	redir_handle(t_redir *redir, t_exec *minishell,t_cmd **cmd)
{
	while (redir)
	{
		if (redir->type == INPUT)
		{
			input_handle(redir, minishell,cmd);
		}
		else if (redir->type == TRUNC)
		{
			output_handle(redir, minishell, cmd, 1);
		}
		else if (redir->type == APPEND)
		{
			output_handle(redir, minishell, cmd, 2);
		}
		else if (redir->type == HEREDOC)
		{
			heredoc(minishell);
		}
		redir = redir->next;
	}
}
