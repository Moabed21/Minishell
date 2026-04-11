/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:37:19 by moabed            #+#    #+#             */
/*   Updated: 2026/04/07 18:48:09 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

// done
void	e_echo(t_cmd *node, t_exec *shell)
{
	int	i;
	int	option;

	option = 0;
	i = 1;
	while (node->args[i] && !ft_strcmp(node->args[i], "-n"))
	{
		i++;
		option = 1;
	}
	while (node->args[i])
	{
		write(node->fd_out, node->args[i], ft_strlen(node->args[i]));
		if (node->args[i + 1])
			write(node->fd_out, " ", 1);
		i++;
	}
	if (option == 0)
		write(node->fd_out, "\n", 1);
	shell->last_status = 0;
}
// Optimize &norm error
void    e_cd(t_cmd *node, t_exec *shell)
{
    char    *path;
    char    old_path[BUFFERSIZE];
    char    *tmp;

    if (node->args[2])
    {
        error_display(2, "cd", ": too many arguments", shell);
        return ;
    }
    getcwd(old_path, BUFFERSIZE); 
    if (!node->args[1])
        path = get_value("HOME", shell->first_env_node);
    else if (!ft_strcmp("-", node->args[1]))
        path = get_value("OLDPWD", shell->first_env_node);
    else
        path = node->args[1];
    if (!path || chdir(path) == -1)
    {
        if (!path)
            write(2, "minishell: cd: path not set\n", 29);
        else
            perror("minishell: cd");
        shell->last_status = 1;
        return ;
    }
    tmp = ft_strjoin("OLDPWD=", old_path);
    replace(tmp, shell->first_env_node);
    free(tmp);
    getcwd(old_path, BUFFERSIZE);
    tmp = ft_strjoin("PWD=", old_path);
    replace(tmp, shell->first_env_node);
    free(tmp);
    shell->last_status = 0;
}

void	e_pwd(t_cmd *node, t_exec *shell)
{
	char	path[BUFFERSIZE];
	t_env	*ptr;

	ptr = shell->first_env_node;
	if (!getcwd(path, BUFFERSIZE))
	{
		while (ptr)
		{
			if (!ft_strncmp(ptr->variable, "PWD=", 4))
			{
				write(node->fd_out, ptr->variable + 4, ft_strlen(ptr->variable
						+ 4));
				break ;
			}
			ptr = ptr->next;
		}
	}
	else
		write(node->fd_out, path, ft_strlen(path));
	write(node->fd_out, "\n", 1);
	shell->last_status = 0;
}

void	e_export(t_cmd *node, t_exec *shell)
{
	int	i;
	int	loc;

	loc = 0;
	i = 1;
	if (!node->args[1])
		e_env(node, shell);
	else
	{
		while (node->args[i])
		{
			if (!replace(node->args[i], shell->first_env_node))
				env_add_last(&shell->first_env_node, node->args[i]);
			i++;
		}
	}
	shell->last_status = 0;
}
// Optimize &norm error
void	e_unset(t_cmd *node, t_exec *shell)
{
	t_env	**curr;
	t_env	*tmp;
	int		i;
	int		len;

	i = 0;
	while (node->args[++i])
	{
		if (!has_no_equal(node->args[i]))
			continue ;
		curr = &shell->first_env_node;
		len = ft_strlen(node->args[i]);
		while (*curr)
		{
			if (!ft_strncmp((*curr)->variable, node->args[i], len)
				&& (*curr)->variable[len] == '=')
			{
				tmp = *curr;
				*curr = (*curr)->next;
				free(tmp->variable);
				free(tmp);
				break ;
			}
			curr = &((*curr)->next);
		}
	}
	shell->last_status = 0;
}
