/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 18:14:48 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 13:36:44 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int res;
	int neg;
	int i;

	res = 0;
	neg = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == 45)
		neg = 1;
	else if (str[i] == 43)
		;
	if (str[i] == 43 || str[i] == 45)
		i++;
	i--;
	while (str[++i] >= '0' && str[i] <= '9')
		res = res * 10 - (str[i] - 48);
	if (neg == 0)
		res = res * -1;
	return (res);
}
