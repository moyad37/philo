/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:17:49 by sgoffaux          #+#    #+#             */
/*   Updated: 2023/03/08 14:10:42 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_return_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (0);
}

static int	ft_check_params(t_rules *rules, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isint(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	rules->count = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->eat_count_max = ft_atoi(argv[5]);
	else
		rules->eat_count_max = 0;
	if (rules->count < 1 || rules->time_to_die < 0 || rules->time_to_eat < 0
		|| rules->time_to_sleep < 0 || rules->eat_count_max < 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_rules	rules;

	rules.max_ate = 0;
	rules.stop_condition = 0;
	if (argc < 5 || argc > 6)
		return (ft_return_error(ERR_USAGE));
	if (!ft_check_params(&rules, argc, argv))
		return (ft_return_error("False parameters check it again.\n"));
	if (!ft_fill(&rules))
		return (ft_return_error("fill error.\n"));
	if (!start_threads(&rules))
		return (ft_return_error("threads error.\n"));
	return (0);
}
