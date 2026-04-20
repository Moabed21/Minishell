/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/04/20 14:00:11 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void	execute_as_is(char *av, char **evar, int fd[2])
{
	char	**args;

	if (!av[0])
		error(3, &fd[2]);
	args = ft_split(av, ' ');
	if (!args || !args[0])
	{
		write(2, "Error : command not found\n", 26);
		free2d_array(args);
		exit(127);
	}
	if (ft_strchr(args[0], '/'))
	{
		execve(args[0], args, evar);
		perror(args[0]);
		free2d_array(args);
		exit(126);
	}
	free2d_array(args);
}

void	execute(char *av, char **evar, int fd[2])
{
	char	**path;
	char	**args;
	char	*firstpart;
	int		i;

	i = -1;
	execute_as_is(av, evar, fd);
	args = ft_split(av, ' ');
	path = findpath(evar);
	if (!args || !args[0] || !path || !evar)
		error(1, fd);
	while (path[++i])
	{
		firstpart = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strjoin(firstpart, args[0]);
		free(firstpart);
		execve(path[i], args, evar);
	}
	firstpart = ft_strjoin(args[0], ": command not found\n");
	i = ft_strlen(firstpart);
	write(2, firstpart, i);
	free(firstpart);
	free2d_array(path);
	free2d_array(args);
}
void	execute_non_builtin(t_exec *shell, t_cmd *node)
{
	ft_fork_pipe(shell,shell->cmds,1);
}
// in execution one cmd we dont need pipe only fork if non builtin , the multiple need both
int	multiple_cmds(t_exec *minishell, t_cmd *cmds_list)
{
	ft_fork_pipe(minishell,minishell->cmds,2);
	ft_fork_pipe(minishell,minishell->cmds,1);
	
}

void	ft_fork_pipe(t_exec *shell, t_cmd *node,int option)
{
	if(option == 1)
	{
		node->fork_id = fork();
		if (node->fork_id == -1)
		{
			shell->last_status = EXIT_FAILURE;
			ruin_everything(shell->cmds);
		}
	}
	else if(option == 2)
	{
		if(pipe(shell->fd) == -1)
		{
			node->fork_id = -1;
			ruin_everything(shell->cmds);
			shell->last_status = EXIT_FAILURE;
		}
	}
}

void	execute_one_cmd(t_exec *shell, t_cmd *node)
{
	if (shell->cmds->redir != NULL)
		redir_handle(shell->cmds->redir, shell, &node);
	if(!node)
		return ;
	node->cmd_type = is_builtin(node);
	if (node->cmd_type != NONE)
		exec_builtin(shell, node, node->cmd_type);
	else
		execute_non_builtin(shell, node);
	if (shell->last_status != 0)
	{
		ruin_everything(shell->cmds);
		return ;
	}
}

void	init_vals(t_cmd *cmds)
{
	while (cmds)
	{
		cmds->fd_in = 0;
		cmds->fd_out = 1;
		cmds = cmds->next;
	}
}

void	execution(t_exec *shell)
{
	//make fork() and enter one of the if statements , then call signal_ignore function to restore the default signals instead of handling it
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
