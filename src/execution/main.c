/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:50:13 by moabed            #+#    #+#             */
/*   Updated: 2026/05/10 20:01:01 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

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

void	main2(t_exec *shell)
{
	char	*input;

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

// 1) display the quit (core du)cat for ctrl \"
// 2) fix the zombie for sleep 100 | sleep 10 |sleep 100
// 3) echo $0asd$0 must display the first $0 value which is minishell
// Syntax cases :
// 1) succeed except the echo $? must be 2 instead of 0
// 2) same number 1 issue , the last status must be 2
// 3) same issue
// 4) same issue ,also the error message must be minishell: .:
// filename argument required instead of minishell: .: command not found
// 5) succeed 100%
// 6) the error message must be checked ,
//	also the last status must be 127 instead of 126
// 7) the error message must be checked , last status is true
// 8) the error message must be checked , last status is true

// Signals cases :
// 1) last status must be 130 instead of 0, behavior true
// 2)
// there is issues with << end the heredoc doesnt work
// signals last status must be checked

// Env cases :
// its only required as "env" only without options or args so , succeed 100%

// Echo cases
// 1) succeed 100%
// 2) succeed 100%
// 3) Not required (not sure of its behaviour)
// 4) succeed 100%
// 5) Not required (not sure of its behaviour)
// 6) succeed 100%
// 7) succeed 100%

// Cd cases
// 1) must be fixed , it displays : minishell: cd: too many arguments ,
//	instead it must print / , last status 2 must be 0
// 2) succeed 100%
// 3) failure 100%
// 4) failure 100%
// 5) succeed 100%
// 6) succeed 100%
// 7) last status wrong must be 1 instead of 2 , else everything okay

// Unset cases
// 1) succeed 100%
// 2) succeed 100%
// 3) succeed 100%
// 4) succeed 100%
// 5) succeed 100%

// Exit cases
// 1) succeed 100%
// 2) succeed 95% (make a quick check on message)
// 3) succeed 100%
// 4) last status must be 2 instead of 0
// 5) succeed 100%
// 6) succeed 100%
// 7) succeed 100%
// 8) succeed 100%
// 9) succeed 100%

// Extra cases
// 1) succeed 100%
// 2) Unknown
// 3) succeed 90%

// Pipe cases
// 1) succeed 100%
// 2) succeed 100%
// 3) succeed 100%
// 4) succeed 90% (WE SHOULDNT PRINT EXIT)
// 5) succeed 90% (WE SHOULDNT PRINT EXIT)
// 6) succeed 100%
// 7) succeed 100%
// 8) succeed 100%
// 9) succeed 100%

// Redir cases
// 1) succeed 100%
// 2) succeed 100%
// 3) failed 100% (causes segfault)
// 4) recheck , last status true
// 5) failed 100% (causes segfault)
// 6) failed 100% (causes segfault)
// 7) succeed 100%

// Expander cases
// 1) failure 90% (last status true)
// 2) recheck the error message we display minishell: “ls: command not found ,
//	the real one minishell: ls -l: Command not found
// 3) recheck (last status false)
// 4) recheck (last status false)
// 5) failure 100%
// 6) recheck

//