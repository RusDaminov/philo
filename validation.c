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

void	ft_wrong_arg_num(void)
{
	printf("-------------------");
	printf("\nWrong args num: ");
	printf("\n1: Number of philosophers");
	printf("\n2: Time to die");
	printf("\n3: Time to eat");
	printf("\n4: Time to sleep");
	printf("\n5: Number of eatings");
	printf("\n-------------------\n");
}

int	ft_is_num(char **av)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
	{
		printf("Wrong philosophers number \n");
		return (0);
	}
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
	{
		printf("Wrong time \n");
		return (0);
	}
	return (1);
}

int	ft_validation(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_wrong_arg_num();
		return (0);
	}
	if (!ft_is_num(av))
		return (0);
	return (1);
}
