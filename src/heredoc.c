/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:57:18 by moabed            #+#    #+#             */
/*   Updated: 2026/05/04 13:56:26 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

void	heredoc(t_exec *shell, t_cmd *node)
{
	char *line;
	char *delimiter;
	int fd[2];

	delimiter = node->args[0];
	if (pipe(fd) == -1)
		return;
	close(fd[1]);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
		}
		
	}
	
}
