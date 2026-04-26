/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/04/26 13:32:44 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void	wait_child(t_exec *shell, t_cmd *node)
{
	int	status;

	waitpid(node->fork_id, &status, 0);
	if (WIFEXITED(status)) // if the chiled died normally
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status)) // if shocked by a signal
		shell->last_status = 128 + WTERMSIG(status);
}
void	ft_fork_pipe(t_exec *shell, t_cmd *node, int option)
{
	if (option == 1)
	{
		node->fork_id = fork();
		if (node->fork_id == -1)
		{
			shell->last_status = EXIT_FAILURE;
			ruin_everything(shell->cmds);
		}
	}
	else if (option == 2)
	{
		if (pipe(shell->fd) == -1)
		{
			node->fork_id = -1;
			shell->last_status = EXIT_FAILURE;
			ruin_everything(shell->cmds);
		}
	}
}
char	**findpath(char **evar)
{
	int		i;
	char	**ev;
	char	*firstpart;

	i = -1;
	while (evar[++i])
	{
		if (ft_strncmp(evar[i], "PATH=", 5) == 0)
		{
			ev = ft_split(evar[i] + 5, ':');
			if (!ev)
				return (NULL);
			break ;
		}
	}
	i = 0;
	while (ev[i])
	{
		firstpart = ft_strjoin(ev[i], "/");
		free(ev[i]);
		ev[i] = firstpart;
		i++;
	}
	return (ev);
}
void	execute_as_is(char **evar, char **av)
{
	if (!av || !av[0])
	{
		write(2, "Error : command not found\n", 26);
		free2d_array(av);
		exit(127);
	}
	if (ft_strchr(av[0], '/'))
	{
		execve(av[0], av, evar);
		perror(av[0]);
		// free2d_array(args);
		exit(126);
	}
	// free2d_array(args);
}

void	execute(t_exec *shell, t_cmd *node)
{
	int		i;
	char	*first_part;
	char	**path;

	i = -1;
	execute_as_is(shell->envp, node->args);
	path = findpath(shell->envp);
	if (!path)
	{
		write(2, "minishell: command not found\n", 28);
		free2d_array(shell->envp);
		exit(127);
	}
	else
		while (path[++i])
		{
			execve(path[i], node->args, shell->envp);
		}
}
void	execute_non_builtin(t_exec *shell, t_cmd *node, int option)
{
	if (option == 1)
		ft_fork_pipe(shell, node, 2);
	ft_fork_pipe(shell, node, 1);
	if (shell->last_status != 0)
	{
		// ruin_everything(shell,option(if there is a pipe or not));
		return ;
	}
	if (node->fork_id == 0)
	{
		default_signals();
		execute(shell, node);
		exit(127);
	}
	wait_child(shell,node);
}
// in execution one cmd we dont need pipe only fork if non builtin ,
//the multiple cmds need both
void	multiple_cmds(t_exec *minishell,t_cmd *cmds_list)
{
	ft_fork_pipe(minishell, cmds_list, 2);
	if (!cmds_list)
		return ;
	while (cmds_list)
	{
		cmds_list = cmds_list->next;
	}
}

void	execute_one_cmd(t_exec *shell, t_cmd *node)
{
	if (node->redir != NULL)
		redir_handle(node->redir, shell, &node);
	if (!node)
		return ;
	exec_builtin(shell, node);
	if (node->cmd_type == NONE)
		execute_non_builtin(shell, node, 0);
	if (shell->last_status != 0)
		return ;
}

void	init_vals(t_cmd *cmds)
{
	while (cmds)
	{
		cmds->fd_in = 0;
		cmds->fd_out = 1;
		cmds->cmd_type = NONE;
		cmds = cmds->next;
	}
}

void	execution(t_exec *shell)
{
	init_vals(shell->cmds);
	if (!shell->cmds->next)
		execute_one_cmd(shell, shell->cmds);
	else
		multiple_cmds(shell, shell->cmds);
	// case 1) having only one command
	// case 2) having one with redir
	// case 3) having 2 cmds (without redirs)
	// case 4) having 2 with redirs
	// the main behavior is to look if there is redirs then execute the command,
	// if there is , execute it then look for the second command if existed
}
