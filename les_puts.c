/*
** my_puts.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:15:12 2016
** Last update Sun Jun  5 21:45:14 2016 
*/

#include <unistd.h>

int	my_putchar(char c)
{
  if ((write(1, &c, 1)) == -1)
    return (-1);
  return (0);
}

int	my_putstr(char *s, int fd)
{
  while (s && *s)
    {
      if ((write(fd, s++, 1)) == -1)
	return (-1);
    }
  return ((fd == 2) ? (-1) : (0));
}

int	my_tputs(char *s, int fd)
{
  if (s == NULL)
    {
      if ((my_putstr("error: problem with tgetstr\n", 1)) == -1)
	return (-1);
      return (-1);
    }
  if ((my_putstr(s, fd)) == -1)
    return (-1);
  return (0);
}

int	my_tputs2(int n1, int n2, int n3)
{
  char	tab[4];
  int	i;

  i = 0;
  tab[0] = n1;
  tab[1] = n2;
  tab[2] = n3;
  tab[3] = 0;
  while (tab[i])
    {
      if ((write(1, &(tab[i]), 1)) == -1)
	return (-1);
      i += 1;
    }
  return (0);
}

int	my_putnbr(int nb)
{
  if (nb < 0)
    {
      if ((my_putchar('-')) == -1)
	return (-1);
      nb = -nb;
    }
  if (nb >= 10)
    {
      if ((my_putnbr(nb / 10)) == -1)
	return (-1);
    }
  if ((my_putchar((nb % 10) + '0')) == -1)
    return (-1);
  return (0);
}
