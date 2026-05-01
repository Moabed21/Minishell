/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:50:13 by moabed            #+#    #+#             */
/*   Updated: 2026/04/29 18:42:21 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

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
		if (g_sig != 0)
		{
			shell.last_status = g_sig;
			g_sig = 0;
		}
		add_history(input);
		shell.cmds = builder(input);
		execution(&shell);
		free(input);
	}
	env_ruin(&shell.first_env_node);
	return (shell.last_status);
}
