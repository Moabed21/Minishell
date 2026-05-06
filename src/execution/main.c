/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:50:13 by moabed            #+#    #+#             */
/*   Updated: 2026/05/06 20:30:24 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

t_cmd	*prepare_for_execution(char *input, char **env, int last_status)
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
// Syntax cases :
// 1) succeed except the echo $? must be 2 instead of 0
// 2) same number 1 issue , the last status must be 2
// 3) same issue
// 4) same issue ,also the error message must be minishell: .: filename argument required instead of minishell: .: command not found
// 5) succeed 100%
// 6) the error message must be checked , also the last status must be 127 instead of 126
// 7) the error message must be checked , last status is true
// 8) the error message must be checked , last status is true

// Signals cases :
// 1) last status must be 130 instead of 0
// there is issues with << end the heredoc doesnt work
// signals last status must be checked

// Env cases :
// 1) succeed 100%
// 2) succeed but check the real $SHELL value
// 3) must be revised , last status true
// 4) same as above (3)
// 5) succedd 100%
// 6) must print the current pwd , it print $OLDPWD , last status correct
// 7) doesnt behave as expected at all 
// 8) same issue as 7
// 9) same

// Echo cases
// 1) succeed 100%
// 2) succeed 100%
// 3) Not required (not sure of its behaviour)
// 4) succeed 100%
// 5) Not required (not sure of its behaviour)
// 6) succeed 100%
// 7) succeed 100%

// Cd cases
// 1) must be fixed , it displays : minishell: cd: too many arguments , instead it must print / , last status 2 must be 0
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
// 2) succeed 95% (make a quick check)
// 3) succeed 100%
// 4) last status must be 2 instead of 0
// 5) last status must be 1 instead of 2
// 6) succeed 100%
// 7) last status must be 1 instead of 2
// 8) succeed 100%
// 9) last status must be 1 instead of 2

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
// 2) recheck the error message we display minishell: “ls: command not found , the real one minishell: ls -l: Command not found
// 3) recheck (last status false)
// 4) recheck (last status false)
// 5) failure 100%
// 6) recheck

//