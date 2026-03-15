/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:44:34 by moabed            #+#    #+#             */
/*   Updated: 2026/03/15 06:23:22 by moabed           ###   ########.fr       */
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
    char **envp;

    envp = findpath(envp);
    
}

void    execute_cmd(t_cmd *cmds_list,char **envp)
{
    //before executing check if there is a redir
    if(cmds_list->redir != NULL)
    {
        redir_handle(&cmds_list->redir, envp);
    }
}

void    execution(t_cmd *cmds_list, char **envp)
{
    //here is the execution tree root
    execute_cmd(cmds_list, envp);
    
    //case 1) having only one command
    //case 2) having one with redir
    //case 3) having 2 cmds (without redirs)
    //case 4) having 2 with redirs

    //the main behavior is to execute the command first then look if there is redirs
    //if there is , execute it then look for the second command if existed
}