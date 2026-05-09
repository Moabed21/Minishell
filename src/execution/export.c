/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:37:19 by moabed            #+#    #+#             */
/*   Updated: 2026/05/08 22:39:26 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

t_env	*export_sorted(t_env *env)
{
	return (env);
}

void	e_export(t_cmd *node, t_exec *shell)
{
	int		i;
	t_env	*export;

	(void)i;
	if (!node->args[1])
	{
		export = export_sorted(shell->first_env_node);
		while (export)
		{
			write(node->fd_out, "declare -x ", 12);
			write(node->fd_out, export->value, ft_strlen(export->value));
			write(node->fd_out, "\n", 1);
			export = export->next;
		}
	}
	else
	{
	}
	shell->last_status = 0;
}
