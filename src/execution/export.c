/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:37:19 by moabed            #+#    #+#             */
/*   Updated: 2026/05/10 10:22:46 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

t_env	*export_sorted(t_env *env)
{
	return (env);
}
int	isvalid(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if()
	}
	
}
void	e_export(t_cmd *node, t_exec *shell)
{
	int		i;
	t_env	*ptr;

	i = 1;
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
			if(is_valid(node->args[i]))
				env_add_last(node.);
		}
		
	}
	shell->last_status = 0;
}
