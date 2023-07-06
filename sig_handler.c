/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:46:50 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 13:47:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	handler_sigquit(void)
{
	rl_on_new_line();
	rl_redisplay();
}

void	handler_sigint(void)
{
	rl_on_new_line();
	ft_putstr("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		handler_sigint();
	if (signal == SIGQUIT)
		handler_sigquit();
}

int	set_signal(void)
{
	struct sigaction	act;
	struct termios		term;

	act.sa_handler = &sig_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	term.c_cflag &= ~ECHOCTL;
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (-1);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
		return (-1);
	return (0);
}