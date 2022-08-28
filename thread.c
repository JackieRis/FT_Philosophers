/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:12:11 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/30 13:25:03 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fork_eat(t_philo *philo)
{
	if (lock_fork(philo) == 0)
	{
		mut_death(philo);
		return (-1);
	}
	speak(philo, MSG_EAT);
	philo->deat = timestamp();
	philo->tbdie = philo->deat + philo->tdie;
	philo->deat += philo->teat;
	while (timestamp() < philo->deat)
	{
		msleep(1);
		if (timestamp() > philo->tbdie)
		{
			mut_death(philo);
			return (-1);
		}
	}
	unlock_forks(philo);
	philo->ndeat++;
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	speak(philo, MSG_SLEEP);
	philo->dsleep = philo->deat + philo->tsleep;
	while (timestamp() < philo->dsleep)
	{
		msleep(1);
		if (timestamp() > philo->tbdie)
			return (-1);
	}
	return (0);
}

static void	*thread_1(void *arg)
{
	t_philo			*philo;

	philo = arg;
	philo->tstamp = timestamp();
	philo->tbdie = philo->tstamp + philo->tdie;
	if (philo->nb_philo == 1)
	{
		solo_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		msleep(philo->teat / 6);
	while (read_death(philo) != -1)
	{
		if (fork_eat(philo) == -1)
			return (NULL);
		if (philo->ndeat >= philo->nteat)
			return (NULL);
		if (philo_sleep(philo) == -1)
			return (NULL);
		speak(philo, MSG_THINK);
	}
	return (NULL);
}

static int	create_philo(t_philo *philo, t_create *c, int i, char **argv)
{
	philo[i].mut_death = &c->mut_death;
	philo[i].nb_philo = c->nb_philo;
	philo[i].id = i + 1;
	philo[i].death = &c->bool;
	philo[i].tdie = ft_atoi(argv[2]);
	philo[i].teat = ft_atoi(argv[3]);
	philo[i].tsleep = ft_atoi(argv[4]);
	philo[i].c = c;
	return (0);
}

int	create_thread(t_philo *philo, t_create *c, int argc, char **argv)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(&c->mut_death, NULL);
	while (i < c->nb_philo)
	{
		philo[i].ndeat = 0;
		philo[i].nteat = INT_MAX;
		if (argc == 6)
			philo[i].nteat = ft_atoi(argv[5]);
		create_philo(philo, c, i, argv);
		if (philo[i].tdie == -1 || philo[i].teat == -1 || \
			philo[i].tsleep == -1)
			return (0);
		i++;
	}
	i = 0;
	while (i < c->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, thread_1, &philo[i]);
		i++;
	}
	c->start_lock = 1;
	return (1);
}
