/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:37:19 by moabed            #+#    #+#             */
/*   Updated: 2026/05/10 17:49:59 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

int	list_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	*export_sorted(t_env *env)
{
	int	env_size;

	env_size = list_size(env);
	
	
	return (env);
}

void	e_export(t_cmd *node, t_exec *shell)
{
	int		i;
	int		has_error;
	t_env	*ptr;

	i = 1;
	has_error = 0;
	if (!node->args[1])
	{
		shell->sorted_env = export_sorted(shell->first_env_node);
		ptr = shell->sorted_env;
        while (ptr)
        {
            write(node->fd_out, "declare -x ", 11);
            write(node->fd_out, ptr->key, ft_strlen(ptr->key));
            if (ptr->value)
            {
                write(node->fd_out, "=\"", 2);
                write(node->fd_out, ptr->value, ft_strlen(ptr->value));
                write(node->fd_out, "\"", 1);
            }
            write(node->fd_out, "\n", 1);
            ptr = ptr->next;
		}
		env_ruin(&shell->sorted_env);
	}
	else
	{
		while (node->args[i])
		{
			if(ft_isalpha(node->args[i][0]) || node->args[i][0] == '_')
				env_add_last(&shell->first_env_node, node->args[i]);
			else
			{
				write(2, "minishell: export: `", 21);
				write(2, node->args[i], ft_strlen(node->args[i]));
				write(2, ": not a valid identifier\n", 26);
				has_error++;
			}
		}
	}
	if(has_error)
		shell->last_status = 1;
	else
		shell->last_status = 0;
}
