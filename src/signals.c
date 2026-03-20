/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:23:25 by moabed            #+#    #+#             */
/*   Updated: 2026/03/20 11:20:20 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//this is the signals part

#include "../headers/execution-part.h"

//break the loop
void    ctrl_d(int sig)
{
    exit(130);
}

void ctrl_c(int pid)
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("",0);
    rl_redisplay();
}

void    do_nothing(int pid)
{
    (void)pid;
    rl_redisplay();
    return ;
}

void    signals_handling()
{
    // CTRL + c
    signal(SIGINT, ctrl_c);
    // signal(); // CTRL + D (EOF)
    signal(SIGQUIT, do_nothing); // CTRL + "\"

    /*using signal function is easy but its not recommended
    due to the differenciation
    */
}
