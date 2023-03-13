/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:12:03 by sgoffaux          #+#    #+#             */
/*   Updated: 2023/03/13 14:08:01 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	new_sleep(unsigned long duration, t_rules *rules)
{
	unsigned long	start;

	start = get_time();
	while (!rules->stop_condition)
	{
		if (get_time() - start >= duration)
			break ;
		usleep(rules->count * 2);
	}
}

static void	*routine(void *params)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)params;
	rules = philo->rules;
	if (philo->pos % 2 && rules->count > 1)
		new_sleep(rules->time_to_eat / 50, rules);
	while (!rules->stop_condition && !rules->max_ate)
	{
		philo_eat(philo);
		philo_print("is sleeping", philo, UNLOCK);
		new_sleep(rules->time_to_sleep, rules);
		philo_print("is thinking", philo, UNLOCK);
	}
	return (NULL);
}

static void	exit_threads(t_rules *rules)
{
	int	i;

	if (rules->count == 1)
		pthread_detach(rules->philos[0].thread_id);
	else
	{
		i = -1;
		while (++i < rules->count)
			pthread_join(rules->philos[i].thread_id, NULL);
	}
	i = -1;
	while (++i < rules->count)
		pthread_mutex_destroy(&rules->forks[i]);
	pthread_mutex_destroy(&rules->meal);
	pthread_mutex_destroy(&rules->writing);
	i = -1;
	while (++i < rules->count)
		free(rules->philos[i].pos_str);
	free(rules->philos);
	free(rules->forks);
}

int	start_threads(t_rules *rules)
{
	int	i;

	i = -1;
	rules->start_time = get_time();
	while (++i < rules->count)
	{
		rules->philos[i].last_ate = get_time();
		if (pthread_create(&rules->philos[i].thread_id,
				NULL, routine, &(rules->philos[i])))
			return (0);
	}
	philo_dead(rules, rules->philos);
	pthread_mutex_unlock(&rules->writing);
	exit_threads(rules);
	return (1);
}
