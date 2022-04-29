/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:09:02 by abernita          #+#    #+#             */
/*   Updated: 2022/04/19 14:09:05 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_structure_init(t_args *options, int ac, char **av)
{
	options->philo_number = ft_atoi(av[1]);
	options->t_die = ft_atoi(av[2]);
	options->t_eat = ft_atoi(av[3]);
	options->t_sleep = ft_atoi(av[3]);
	options->f_is_dead = 0;
	options->total_eat = 0;
	options->t_start = ft_current_time();
	if (ac == 5)
		options->nbr_of_eating = -1;
	if (ac == 6)
		options->nbr_of_eating = ft_atoi(av[5]);
	options->forks = malloc((options->philo_number + 1)
			* sizeof(pthread_mutex_t));
	pthread_mutex_init(&options->lock_print, NULL);
	return (1);
}

void	ft_init_philos(t_args *options, t_philos *philos, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < options->philo_number)
	{
		pthread_mutex_init(&options->forks[i], NULL);
		philos[i].id = i + 1;
		philos[i].right_fork = &options->forks[i];
		philos[i].t_last_eated = 0;
		philos[i].nbr_eated = 0;
		philos[i].args = options;
		if (i != options->philo_number - 1)
			philos[i].left_fork = &options->forks[i + 1];
		else
			philos[i].left_fork = &options->forks[0];
		pthread_create(&threads[i], NULL, ft_philo_lifecycle,
			(void *)(&philos[i]));
	}
	options->philo_arr = philos;
}
