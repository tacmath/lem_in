/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_two_s_complement.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/03 14:05:06 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/02 10:26:37 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

unsigned int		ft_compl(int a)
{
	unsigned int	b;

	if (a < 0)
	{
		a = -a;
		b = (~a) + 1;
	}
	else
		b = a;
	return (b);
}

unsigned long int	ft_lcompl(long int a)
{
	unsigned long int	b;

	if (a < 0)
	{
		a = -a;
		b = (~a) + 1;
	}
	else
		b = a;
	return (b);
}

unsigned long int	ft_llcompl(long long int a)
{
	unsigned long long int	b;

	if (a < 0)
	{
		a = -a;
		b = (~a) + 1;
	}
	else
		b = a;
	return (b);
}
