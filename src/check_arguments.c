/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:22:04 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/02/26 18:34:56 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	check_pid(char *pid)
{
	int		pid_num;
	int		length;
	int		i;
	long	temp;

	i = ft_is_digit_string(pid);
	if (i == 0)
		return (0);
	length = ft_strlen(pid);
	temp = atol(pid);
	if ((length == 10 && pid[0] != '-' && ft_strncmp(pid, INT_MAX_STRING,
				10) > 0 && temp > INT_MAX) || (length == 11 && pid[0] == '-'
			&& ft_strncmp(pid, INT_MIN_STRING, 11) > 0 && temp < INT_MIN)
		|| (length > 11 && (temp > INT_MAX || temp < INT_MIN)))
	{
		ft_printf("Please provide the correct server PID (int size digit)\n");
		return (0);
	}
	pid_num = ft_atoi(pid);
	if (pid_num <= 0)
	{
		ft_printf("Please provide the correct server PID (positive digit)\n");
		return (0);
	}
	return (1);
}

int	check_arguments(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Please provide only two arguments");
		return (1);
	}
	if (!check_pid(argv[1]))
		return (1);
	if (argv[2] == NULL)
	{
		ft_printf("please provide a proper string\n");
		return (1);
	}
	return (0);
}

long	ft_atol(const char *str)
{
	long	i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}
