/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:49:22 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/02/23 20:09:46 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_convert_signal(int signum, int bits, char *c)
{
	if (signum == SIGUSR1 && bits != 8)
		*c = *c | (1 << bits);
	else if (signum == SIGUSR2 && bits != 8)
		*c = *c | (0 << bits);
}

void	print_message(char **message)
{
	ft_putstr_fd(*message, 1);
	ft_putchar_fd('\n', 1);
	free(*message);
	*message = NULL;
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	bits;
	static char	c;
	static char	*message;

	(void)context;
	if (!info->si_pid)
		exit(0);
	ft_convert_signal(signum, bits, &c);
	if (++bits == 8)
	{
		bits = 0;
		if (c == '\0')
		{
			print_message(&message);
			error_kill_free(info->si_pid, SIGUSR1, message);
			return ;
		}
		if (!message)
			message = ft_strdup(&c);
		else
			message = ft_strjoin(message, &c);
		check_message(message);
		c = 0;
	}
	error_kill_free(info->si_pid, SIGUSR1, message);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	pid_t				pid_server;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &sig_handler;
	(void)argv;
	if (argc != 1)
	{
		ft_printf("Do not provide any other arguments");
		return (1);
	}
	pid_server = getpid();
	ft_printf("the PID is %d\n", pid_server);
	error_sigaction(&sa, SIGUSR1);
	error_sigaction(&sa, SIGUSR2);
	while (1)
		pause();
	return (0);
}
