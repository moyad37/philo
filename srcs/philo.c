/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:10:57 by sgoffaux          #+#    #+#             */
/*   Updated: 2023/03/06 12:01:40 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_print(char *msg, t_philo *philo, int unlock)
{
	if(!pthread_mutex_lock(&philo->rules->haupt))
	{
	char	*timestamp;
	//(void)unlock;
	timestamp = ft_itoa(get_time() - philo->rules->start_time);
	pthread_mutex_lock(&philo->rules->writing);
	if (!philo->rules->stop_condition && !philo->rules->max_ate)
		printf("%s %s %s\n", timestamp, philo->pos_str, msg);
	if(unlock)
		pthread_mutex_unlock(&philo->rules->writing);
	free(timestamp);
	pthread_mutex_unlock(&philo->rules->haupt);
	}
}

void	philo_eat(t_philo *philo)
{
	//if(!pthread_mutex_lock(&philo->rules->haupt))
	//{
		pthread_mutex_lock(&philo->rules->forks[philo->ffork]);
		philo_print("has taken a fork", philo, UNLOCK);
		pthread_mutex_lock(&philo->rules->forks[philo->sfork]);
		philo_print("has taken a fork", philo, UNLOCK);
	//}
		pthread_mutex_lock(&philo->rules->meal);
		philo_print("is eating", philo, UNLOCK);
		philo->last_ate = get_time();
		pthread_mutex_unlock(&philo->rules->meal);
		new_sleep(philo->rules->time_to_eat, philo->rules);
		pthread_mutex_unlock(&philo->rules->forks[philo->sfork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->ffork]);
		philo->ate_times++;
}

void	philo_dead(t_rules *rules, t_philo *philo)
{
	int	i;

	while (!rules->max_ate)
	{
		i = -1;
		while (++i < rules->count && !rules->stop_condition)
		{
			//if(!pthread_mutex_lock(&philo->rules->haupt))
			//{
				//pthread_mutex_lock(&rules->meal);
				if ((int)(get_time() - philo[i].last_ate) >= rules->time_to_die)
				{
					philo_print("died", &philo[i], LOCK);
					rules->stop_condition = 1;
				}
				//pthread_mutex_unlock(&philo->rules->haupt);
			//}
			//pthread_mutex_unlock(&rules->meal);
		}
		if (rules->stop_condition)
			break ;
		i = 0;
		while (rules->eat_count_max && i < rules->count
			&& philo[i].ate_times >= rules->eat_count_max)
			i++;
		rules->max_ate = (i == rules->count);
	}
}
