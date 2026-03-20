/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:50:13 by moabed            #+#    #+#             */
/*   Updated: 2026/03/20 11:53:47 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void    shell_protection()
{
    // if(!isatty(STDIN_FILENO))
        // exit(3);
    
}

int main(int ac,char **av,char **envp)
{
    t_cmd *cmds_list;
    
    signals_handling();
    char *input;
    // while (1)
    // {
            shell_protection();
            input = readline("minishell> ");
            add_history(input);
            cmds_list = parsing(input);
            execution(cmds_list, envp);
    // }
    //the return value will bw the last status of execution
}
