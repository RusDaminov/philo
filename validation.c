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
	printf(BLU "-------------------");
	printf(GRN "\nWrong arguments number: ");
	printf(GRN "\n1: Number of philosophers");
	printf(GRN "\n2: Time to die");
	printf(GRN "\n3: Time to eat");
	printf(GRN "\n4: Time to sleep");
	printf(GRN "\n5: Number of eatings");
	printf(BLU "\n-------------------\n" RESET);
}

int	ft_is_num(char **av)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
	{
		printf(RED "Wrong philosophers number \n" RESET);
		return (0);
	}
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
	{
		printf(RED "Wrong time \n" RESET);
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
