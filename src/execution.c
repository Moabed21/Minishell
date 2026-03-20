/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/03/20 13:02:45 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

char	**findpath(char **evar)
{
	int	i;

	i = 0;
	while (evar[i])
	{
		if (ft_strncmp(evar[i], "PATH=", 5) == 0)
			return (ft_split(evar[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void    redir_handle(t_redir **redir, char **envp)
{
	
}

void    execute_one_cmd(t_cmd *cmds_list, char **envp)
{
	//before executing check if there is a redir
	if(cmds_list->redir != NULL)
	{
		redir_handle(&cmds_list->redir, envp);
	}
}
t_env *env_init(char **env)
{
	t_env **environment;
	int size;
	
	size = 0;
	while(env[size])
	{
		size++;
	}
	environment = malloc(sizeof(t_env *)*size);
	
}
void    execution(t_cmd *cmds_list, char **envp)
{
	t_env *env;
	
	env = env_init(envp);
	//here is the execution tree root
	if (!cmds_list->next)
		execute_one_cmd(cmds_list, env);
	else
		multiple_cmds(cmds_list, env);
	//case 1) having only one command
	//case 2) having one with redir
	//case 3) having 2 cmds (without redirs)
	//case 4) having 2 with redirs

	//the main behavior is to execute the command first then look if there is redirs
	//if there is , execute it then look for the second command if existed
}