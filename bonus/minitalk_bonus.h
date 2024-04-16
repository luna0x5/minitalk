/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 06:12:27 by hmoukit           #+#    #+#             */
/*   Updated: 2024/04/16 17:01:05 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

/*functions from libft*/
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);

/*other functions that I used*/
void	initialize_buffer(char (*buffer)[4]);
int		check_byte(char c);

#endif
