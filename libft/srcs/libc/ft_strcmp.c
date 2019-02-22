/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 16:29:54 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 13:07:38 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *in1;
	unsigned char *in2;

	in1 = (unsigned char *)s1;
	in2 = (unsigned char *)s2;
	in1--;
	in2--;
	while (*(++in1) == *(++in2) && (*in1 != '\0' || *in2 != '\0'))
		;
	return (*(in1) - *(in2));
}
