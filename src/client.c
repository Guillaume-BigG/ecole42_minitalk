/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:49:09 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/02/23 20:09:59 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_usr1_received;

void	sigusr_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	g_usr1_received = 1;
}

void	send_bits(pid_t pid_server, char c)
{
	int	bits;
	int	wait_time;

	bits = 0;
	while (bits < 8)
	{
		wait_time = 0;
		if ((c & (1 << (bits))) != 0)
			error_kill(pid_server, SIGUSR1);
		else
			error_kill(pid_server, SIGUSR2);
		bits++;
		while (g_usr1_received != 1)
		{
			if (wait_time == 100)
			{
				ft_printf("Signal never received back\n");
				exit(0);
			}
			wait_time++;
			pause();
		}
		g_usr1_received = 0;
	}
}

void	send_message(pid_t pid_server, char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		send_bits(pid_server, string[i]);
		i++;
	}
	send_bits(pid_server, '\0');
	exit(0);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	pid_t				pid_server;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &sigusr_handler;
	error_sigaction(&sa, SIGUSR1);
	if (check_arguments(argc, argv))
		return (1);
	pid_server = ft_atoi(argv[1]);
	send_message(pid_server, argv[2]);
}
