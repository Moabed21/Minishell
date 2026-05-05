/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:50:13 by moabed            #+#    #+#             */
/*   Updated: 2026/05/05 17:05:46 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_exec	shell;

	(void)ac;
	(void)av;
	if (shell_init(envp, &shell))
		return (1);
	while (1)
	{
		interactive_signals();
		input = readline("minishell> ");
		if (!input)
			break ;
		add_history(input);
		shell.cmds = prepare_for_execution(input, envp, shell.last_status);
		if(g_sig != 0)
		{
			shell.last_status = g_sig;
			g_sig = 0;
		}
		if (shell.cmds)
		{
			execution(&shell);
			free_cmds_list(&shell.cmds);
		}
		free(input);
	}
	//ctrl c + ctrl d causes segfault , ruin everything is a reason
	ruin_everything(&shell);
	return (shell.last_status);
}
