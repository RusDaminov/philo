/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:02:06 by abernita          #+#    #+#             */
/*   Updated: 2022/04/19 15:02:08 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_print(t_all *all, int id, char *str)
{
	sem_wait(all->message);
	if (!(all->dead))
	{
		printf(WHT "%lli ", timestamp() - all->time_start);
		printf(WHT "%i ", id + 1);
		printf(RED "%s\n", str);
	}
	sem_post(all->message);
	return ;
}

int	error_message(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, RED "Error", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (error_message(RED "At least one wrong argument"));
	if (error == 2)
		return (error_message(RED "Semaphore initialisation error"));
	return (1);
}
