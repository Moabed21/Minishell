/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/04/11 17:23:52 by moabed           ###   ########.fr       */
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

static void	execute(char *av, char **evar, int fd[2])
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

void	ruin_everything(t_exec *shell)
{
	//postponed until i know from partner how its malloc'd
}

int	multiple_cmds(t_exec *minishell, t_cmd *cmds_list)
{
	if (pipe(minishell->fd) == -1)
		ruin_everything(cmds_list);
	cmds_list->fork_id = fork();
	if (cmds_list->fork_id == -1)
	{
		ruin_everything(cmds_list);
	}
}

void	p_fork_exec(t_exec *shell, t_cmd *node)
{
	node->fork_id = fork();
	if (node->fork_id == -1)
	{
		shell->last_status = EXIT_FAILURE;
	}
}

void	execute_one_cmd(t_exec *shell, t_cmd *node)
{
	if (shell->cmds->redir != NULL)
	{
		redir_handle(shell->cmds->redir, shell);
	}
	node->cmd_type = is_builtin(node);
	if (node->cmd_type != NONE)
	{
		exec_builtin(shell, node, node->cmd_type);
		return ;
	}
	p_fork_exec(shell, node);
	if (shell->last_status != 0)
	{
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
	shell->cmds->fork_id = fork();
	if(shell->cmds->fork_id == -1)
	{
		ruin_everything(shell);
		return;
	}
	if(shell->cmds->fork_id == 0)
	{
		default_signals();
		if (!shell->cmds->next)
			execute_one_cmd(shell, shell->cmds);
		else
			multiple_cmds(shell, shell->cmds);	
	}
	// case 1) having only one command
	// case 2) having one with redir
	// case 3) having 2 cmds (without redirs)
	// case 4) having 2 with redirs
	// the main behavior is to look if there is redirs then execute the command,
	// if there is , execute it then look for the second command if existed
}
