/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:14:24 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/05 17:14:09 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsingpart.h"

void	errmsg(char *errmsg, char *detail, int check)
{
	char	*msg;
	char	*tmp;
	
	msg = ft_strdup("minishell: ");
	tmp = msg;
	msg = ft_strjoin(msg, errmsg);
	free(tmp);
	tmp = msg;
	if (check)
		msg = ft_strjoin(msg, " `");
	else
		msg = ft_strjoin(msg, ": ");
	free(tmp);
	tmp = msg;
	msg = ft_strjoin(msg, detail);
	free(tmp);
	if (check)
	{
		tmp = msg;
		msg = ft_strjoin(msg, "'");
		free(tmp);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr((void **)&msg);
}
