/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error-handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:19:58 by moabed            #+#    #+#             */
/*   Updated: 2026/04/26 07:29:42 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void	error_display(int fd, char *cmd, char *right_end, t_exec *shell)
{
	int	cmdlen;
	int	rightlen;

	rightlen = ft_strlen(right_end);
	cmdlen = ft_strlen(cmd);
	write(fd, "minishell: ", 12);
	write(fd, cmd, cmdlen);
	write(fd, right_end, rightlen);
	write(fd, "\n", 1);
	shell->last_status = 2;
}

void	free_current_cmd(t_cmd **node)
{
}

void	ruin_everything(t_exec *shell)
{
	// postponed until i know from partner how its malloc'd
}