/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:27:20 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/02/23 20:09:35 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	error_sigaction(struct sigaction *sa, int signum)
{
	int	error;

	error = sigaction(signum, sa, NULL);
	if (error == -1)
	{
		ft_printf("Error from sigaction, exiting process\n");
		exit(0);
	}
}

void	error_kill(pid_t pid, int signum)
{
	int	error;

	error = kill(pid, signum);
	if (error == -1)
	{
		ft_printf("Error from kill, exiting process\n");
		exit(0);
	}
}

void	error_kill_free(pid_t pid, int signum, char *message)
{
	int	error;

	error = kill(pid, signum);
	if (error == -1)
	{
		ft_printf("Error from kill, exiting process\n");
		free(message);
		exit(0);
	}
}

int	ft_is_digit_string(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
		{
			ft_printf("Please provide the correct server PID (only digit)\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	check_message(char *message)
{
	if (!message)
	{
		free(message);
		exit(0);
	}
}
