/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/03/22 13:15:17 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void	input_handle(t_redir *redir, t_exec *instance)
{
	int fd;
	
}
void	redir_handle(t_redir *redir, t_exec *instance)
{
	if (redir->type == INPUT)
	{
		input_handle(redir, instance);
	}
	
}

void	execute_one_cmd(t_cmd *cmds_list, t_exec *instance)
{
	// before executing check if there is a redir
	if (cmds_list->redir != NULL)
	{
		redir_handle(cmds_list->redir, instance);
	}
}
ruin_everything(t_cmd *cmds_list, t_env *first_env_node)
{
	
}
void	multiple_cmds(t_cmd *cmds_list, t_exec *instance)
{
	if(pipe(instance->fd) == -1)
		ruin_everything(cmds_list,instance->first_env_node);
	instance->fork_id = fork();
	if(instance->fork_id == -1)
	{}
}

void	execution(t_cmd *cmds_list, char **envp)
{
	t_env	*env;
	t_exec	instance;

	env = env_init(envp);
	instance.first_env_node = env;
	// here is the execution tree root
	if (!cmds_list->next)
		execute_one_cmd(cmds_list, &instance);
	else
		multiple_cmds(cmds_list, &instance);
	// case 1) having only one command
	// case 2) having one with redir
	// case 3) having 2 cmds (without redirs)
	// case 4) having 2 with redirs
	// the main behavior is to execute the command first then look if there is redirs
	// if there is , execute it then look for the second command if existed
}
