/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:52:51 by abernita          #+#    #+#             */
/*   Updated: 2022/04/07 20:53:10 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	unsigned int	i;
	int				sign;
	unsigned long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (((str[i] > 8) && (str[i] < 14)) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] && str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if ((sign == -1) && (res > 9223372036854775808u))
		return (0);
	if ((sign == 1) && (res >= 9223372036854775808u))
		return (-1);
	return (sign * res);
}

long	ft_current_time(void)
{
	struct timeval	t_start;

	gettimeofday(&t_start, NULL);
	return (t_start.tv_sec * 1000 + t_start.tv_usec / 1000);
}

void	ft_mysleep(int ms)
{
	long	time;

	time = ft_current_time();
	usleep(ms * 920);
	while (ft_current_time() < time + ms)
		usleep(ms * 3);
}

int	ft_time_passed(long t_start)
{
	return ((int)(ft_current_time() - t_start));
}

void	ft_join_clean(t_args *s_options, t_philos *philos, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < s_options->philo_number)
		pthread_join(threads[i], NULL);
	i = -1;
	while (++i < s_options->philo_number)
	{
		pthread_mutex_unlock(&s_options->forks[i]);
		pthread_mutex_destroy(&s_options->forks[i]);
	}
	free(threads);
	free(s_options->forks);
	free(philos);
}
