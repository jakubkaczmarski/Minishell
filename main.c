/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:12:03 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/07 08:21:41 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@param argc -> amount of arguments
@param argv -> arguments as array
@param envv -> enviromental variables as array
*/
int main(int argc, char **argv, char **envv)
{
	replace_envv(envv);
	printf("%d,%s\n", argc, argv[0]);
	return (0);
}