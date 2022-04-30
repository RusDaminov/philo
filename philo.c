/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:57:35 by abernita          #+#    #+#             */
/*   Updated: 2022/04/07 18:57:37 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_lifecycle(void *philosopher)
{
	t_philos	*philo;

	philo = philosopher;
	if (philo->id % 2 == 0)
		ft_mysleep((int)philo->args->t_eat);
	while (philo->args->f_is_dead != 1
		&& philo->nbr_eated != philo->args->nbr_of_eating)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->args->lock_print);
		printf(MAG "%d: %d took a left fork\n" RESET,
			ft_time_passed(philo->args->t_start), philo->id);
		pthread_mutex_unlock(&philo->args->lock_print);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->args->lock_print);
		printf(MAG "%d: %d took a right fork\n" RESET,
			ft_time_passed(philo->args->t_start), philo->id);
		pthread_mutex_unlock(&philo->args->lock_print);
		ft_philo_eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_philo_sleeping(philo);
		ft_philos_thinking(philo);
	}
	return (NULL);
}

int	stop(t_philos *philo, t_args *data, int i)
{
	if (data->t_die + 1 <= ft_time_passed(data->t_start)
		- philo[i].t_last_eated)
	{
		data->f_is_dead = 1;
		pthread_mutex_lock(&philo->args->lock_print);
		printf(RED"%d: %d died\n" RESET,
			ft_time_passed(philo->args->t_start), philo->id);
		return (1);
	}
	if (philo[i].nbr_eated == data->nbr_of_eating)
	{
		data->total_eat++;
		if (data->total_eat == data->philo_number)
			return (1);
	}
	return (0);
}

void	*ft_should_philo_die(void *tmp)
{
	int			i;
	t_philos	*philo;
	t_args		*data;

	philo = tmp;
	data = philo[0].args;
	while (1)
	{
		data->total_eat = 0;
		i = 0;
		while (i < data->philo_number)
		{
			if (stop(philo, data, i))
				return (0);
			i++;
			ft_mysleep(1);
		}
	}
}

int	main(int ac, char **av)
{
	t_args		s_options;
	t_philos	*philos;
	pthread_t	*threads;
	int			i;

	i = 0;
	if (ft_validation(ac, av) == 0)
		return (0);
	if (ft_structure_init(&s_options, ac, av) == 0)
		return (0);
	philos = malloc(s_options.philo_number * sizeof(t_philos));
	threads = malloc((s_options.philo_number + 1) * sizeof(pthread_t));
	ft_init_philos(&s_options, philos, threads);
	pthread_create(&threads[i], NULL, &ft_should_philo_die, (void *)(philos));
	ft_join_clean(&s_options, philos, threads);
	if (s_options.total_eat == s_options.philo_number)
		printf(GRN "[ All the philosophers are ate ]\n" RESET);
	return (0);
}
