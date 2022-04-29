/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:57:35 by abernita          #+#    #+#             */
/*   Updated: 2022/04/07 18:57:37 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_semaphore(t_all *all)
{
	sem_unlink("forks");
	sem_unlink("message");
	sem_unlink("mealcheck");
	all->forks = sem_open("forks", O_CREAT, S_IRWXU, all->philo_count);
	all->message = sem_open("message", O_CREAT, S_IRWXU, 1);
	all->meal_check = sem_open("mealcheck", O_CREAT, S_IRWXU, 1);
	if (all->forks <= 0 || all->message <= 0 || all->meal_check <= 0)
		return (1);
	return (0);
}

int	init_philo(t_all *all)
{
	int	i;

	i = all->philo_count;
	while (--i >= 0)
	{
		all->philo[i].name = i;
		all->philo[i].x_ate = 0;
		all->philo[i].last_meal = 0;
		all->philo[i].all = all;
	}
	return (0);
}

int	init_all(t_all *all, char **av)
{
	all->philo_count = ft_atoi(av[1]);
	all->time_die = ft_atoi(av[2]);
	all->time_eat = ft_atoi(av[3]);
	all->time_sleep = ft_atoi(av[4]);
	all->dead = 0;
	if (all->philo_count < 1 || all->time_die < 60 || all->time_eat < 60
		|| all->time_sleep < 60 || all->philo_count > 250)
		return (1);
	if (av[5])
	{
		all->eat_count = ft_atoi(av[5]);
		if (all->eat_count <= 0)
			return (1);
	}
	else
		all->eat_count = -1;
	if (all->eat_count == 1)
		all->eat_count++;
	if (init_semaphore(all))
		return (2);
	init_philo(all);
	return (0);
}
