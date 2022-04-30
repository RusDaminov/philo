/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:26:54 by abernita          #+#    #+#             */
/*   Updated: 2022/04/19 16:26:56 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *philo)
{
	t_all	*all;

	all = philo->all;
	sem_wait(all->forks);
	action_print(all, philo->name, MAG "has taken left fork" RESET);
	sem_wait(all->forks);
	action_print(all, philo->name, MAG "has taken right fork" RESET);
	sem_wait(all->meal_check);
	action_print(all, philo->name, YEL "is eating" RESET);
	philo->last_meal = timestamp();
	sem_post(all->meal_check);
	smart_sleep(all->time_eat, all);
	(philo->x_ate)++;
	sem_post(all->forks);
	sem_post(all->forks);
}

void	*death_checker(void *void_philo)
{
	t_philo	*philo;
	t_all	*all;

	philo = (t_philo *)void_philo;
	all = philo->all;
	while (42)
	{
		sem_wait(all->meal_check);
		if (time_diff(philo->last_meal, timestamp()) > all->time_die)
		{
			action_print(all, philo->name, RED "dead" RESET);
			all->dead = 1;
			sem_wait(all->message);
			exit(1);
		}
		sem_post(all->meal_check);
		if (all->dead)
			break ;
		usleep(1000);
		if (philo->x_ate >= all->eat_count && all->eat_count != -1)
			break ;
	}
	return (NULL);
}

void	p_process(void *void_philo)
{
	t_philo	*philo;
	t_all	*all;

	philo = (t_philo *)void_philo;
	all = philo->all;
	philo->last_meal = timestamp();
	pthread_create(&(philo->death_check), NULL, death_checker, void_philo);
	if (philo->name % 2)
		usleep(42);
	while (!(all->dead))
	{
		philo_eats(philo);
		if (philo->x_ate >= all->eat_count && all->eat_count != -1)
			break ;
		action_print(all, philo->name, BLU "is sleeping" RESET);
		smart_sleep(all->time_sleep, all);
		action_print(all, philo->name, GRN "is thinking" RESET);
	}
	pthread_join(philo->death_check, NULL);
	if (all->dead)
		exit(1);
	exit(0);
}

void	exit_launcher(t_all *all)
{
	int	i;
	int	ret;

	i = 0;
	while (i < all->philo_count)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < all->philo_count)
				kill(all->philo[i].proc_id, 15);
			break ;
		}
		i++;
	}
	sem_close(all->forks);
	sem_close(all->message);
	sem_close(all->meal_check);
	sem_unlink("forks");
	sem_unlink("message");
	sem_unlink("meal_check");
}

int	launcher(t_all *all)
{
	int		i;
	t_philo	*phi;

	i = -1;
	phi = all->philo;
	all->time_start = timestamp();
	while (++i < all->philo_count)
	{
		phi[i].proc_id = fork();
		if (phi[i].proc_id < 0)
			return (1);
		if (phi[i].proc_id == 0)
			p_process(&(phi[i]));
		usleep(100);
	}
	exit_launcher(all);
	return (0);
}
