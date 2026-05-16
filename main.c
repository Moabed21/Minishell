/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:50:13 by moabed            #+#    #+#             */
/*   Updated: 2026/05/16 15:30:55 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/executionpart.h"
#include "headers/parsingpart.h"

t_cmd	*prepare_for_execution(char *input, t_env *env, int last_status)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenization(input);
	if (!tokens)
		return (NULL);
	if (check_if_var(&tokens) == FAILURE)
	{
		tokenlistclear(&tokens);
		return (NULL);
	}
	if (!expand_tokens(&tokens, env, last_status))
	{
		tokenlistclear(&tokens);
		return (NULL);
	}
	cmds = parsing(tokens);
	tokenlistclear(&tokens);
	return (cmds);
}

int	check_line(char *input)
{
	int	i;
	int	option;

	option = 0;
	i = 0;
	while (input[i])
	{
		if (!(input[i] == ' ' || (input[i] >= 9 && input[i] <= 13)))
			option = 1;
		i++;
	}
	return (option);
}

void    main2(t_exec *shell)
{
	char    *input;

	while (1)
	{
		interactive_signals();
		input = readline("minishell> ");
		if (g_sig != 0)
		{
			shell->last_status = g_sig;
			g_sig = 0;
		}
		if (!input)
			break ;
		if(check_line(input))
			add_history(input);
		shell->cmds = prepare_for_execution(input, shell->first_env_node,
				shell->last_status);
		if (shell->cmds)
		{
			execution(shell);
			free_cmds_list(&shell->cmds);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_exec	shell;

	(void)ac;
	(void)av;
	if (shell_init(envp, &shell))
		return (1);
	main2(&shell);
	ruin_everything(&shell);
	return (shell.last_status);
}
