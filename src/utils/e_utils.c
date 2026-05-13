/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 06:03:41 by moabed            #+#    #+#             */
/*   Updated: 2026/05/11 18:39:19 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	init_vals(t_exec *shell, t_cmd *cmds)
{
	shell->cmds_count = 0;
	while (cmds)
	{
		check_cmds(cmds);
		cmds->fd_in = 0;
		cmds->fd_out = 1;
		cmds->fork_id = 0;
		shell->cmds_count++;
		cmds = cmds->next;
	}
}

