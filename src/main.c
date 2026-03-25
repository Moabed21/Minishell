/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:50:13 by moabed            #+#    #+#             */
/*   Updated: 2026/03/24 19:41:09 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

int main(int ac,char **av,char **envp)
{
    t_exec shell;
    char *input;
    
    shell.last_status = 0;
    while (1)
    {
        signals_handling();
        shell_protection();
        input = readline("minishell> ");
        if(!input)
            break;
        if(global_sig !=0)
        {
            shell.last_status = global_sig;
            global_sig = 0;
        }
        add_history(input);
        shell.cmds = parsing(input);
        execution(&shell, envp);
        free(input);
    }
    return (shell.last_status);
    //the return value will bw the last status of execution
}
