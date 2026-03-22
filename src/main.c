/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:50:13 by moabed            #+#    #+#             */
/*   Updated: 2026/03/22 10:38:12 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

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
