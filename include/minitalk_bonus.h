/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:04:40 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/02/26 18:31:46 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "../libft/include/ft_printf.h"
# include "../libft/include/libft.h"
# include <signal.h>
# include <stdio.h>
# include <strings.h>
# include <sys/types.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define INT_MAX_STRING "2147483647"
# define INT_MIN_STRING "-2147483648" 

int		ft_is_digit_string(char *string);
void	error_kill(pid_t pid, int signal);
void	error_kill_free(pid_t pid, int signal, char *message);
void	error_sigaction(struct sigaction *sa, int signal);
int		check_pid(char *pid);
int		check_arguments(int argc, char **argv);
void	check_message(char *message);
long	ft_atol(const char *str);

#endif