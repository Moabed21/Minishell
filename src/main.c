/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:50:13 by moabed            #+#    #+#             */
/*   Updated: 2026/04/11 09:16:13 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_exec	shell;

	if(shell_init(envp,&shell))
		return(1);
	while (1)
	{
		interactive_signals();
		input = readline("minishell> ");
		if (!input)
			break ;
		if (global_sig != 0)
		{
			shell.last_status = global_sig;
			global_sig = 0;
		}
		add_history(input);
		shell.cmds = builder(input);
		execution(&shell);
		free(input);
	}
	return (shell.last_status);
	// the return value will bw the last status of execution
}
