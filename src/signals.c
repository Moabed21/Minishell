/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:23:25 by moabed            #+#    #+#             */
/*   Updated: 2026/03/09 12:38:51 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//this is the signals part

#include "execution-part.h"

void    quit_sig(int sig)
{
    printf("Quit Succeed\n");
    exit(1);
}
void    do_nothing(int pid)
{
    return ;
}
void    signals_handling()
{
    signal(SIGINT, quit_sig); // CTRL + c
    signal(SIGINT, quit_sig); // CTRL +
    signal(SIGQUIT, do_nothing); // CTRL + "\"
}

int main(int ac,char**av,char**envp)
{
    char *s;
    signals_handling();
    while (1)
    {
        // shell_protection(function)
        // parsing
        //execution
    }
    
}
