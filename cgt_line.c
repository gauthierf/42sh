/*
** change_line.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:15:23 2016
** Last update Sun Jun  5 19:13:25 2016 retyt
*/

#include <unistd.h>
#include "readline.h"
#include "my.h"

static int	write_line_up(char *str)
{
  int		i;

  i = 0;
  if ((my_putstr("\033[1A", 1)) == -1)
    return (-1);
  while (i < 1000)
    {
      if ((my_tputs(str, 1)) == -1)
	return (-1);
      i += 1;
    }
  return (1);
}

int	line_up(void)
{
  char	buffer[32];
  int	size_read;
  int	i;
  char	str[4];

  str[0] = 27;
  str[1] = 91;
  str[2] = 67;
  str[3] = 0;
  if ((my_putstr("\033[6n", 1)) == -1)
    return (-1);
  if ((size_read = read(0, buffer, 31)) == -1)
    return (my_putstr("error: could not read\n", 2));
  i = 0;
  while (buffer[i] && buffer[i] != ';')
    i += 1;
  if (buffer[i] && buffer[i + 1] == '1' && buffer[i + 2] == 'R')
    return (write_line_up(str));
  return (0);
}

static int	my_little_atoi(char *str)
{
  int		i;
  int		number;

  i = 0;
  number = 0;
  while (str[i] >= 48 && str[i] <= 57)
    {
      number *= 10;
      number += (str[i] - 48);
      i++;
    }
  return (number);
}

static int	write_line_down(int size)
{
  char		*left;
  int		i;

  i = 0;
  if ((write(1, "\033[1B", 4)) == -1)
    return (-1);
  if ((left = tgetstr("le", NULL)) == NULL)
    return (my_putstr("error: tgetstr\n", 2));
  while (i < size)
    {
      if ((write(1, left, 1)) == -1)
	return (-1);
      i += 1;
    }
  return (0);
}

int	line_down(int size)
{
  char	buffer[32];
  char	str[4];
  int	size_read;
  int	i;
  int	tmp;

  str[0] = 27;
  str[1] = 91;
  str[2] = 67;
  str[3] = 0;
  if ((write(1, "\033[6n", 4)) == -1)
    return (-1);
  if ((size_read = read(0, buffer, 31)) == -1)
    return (my_putstr("error: could not read\n", 2));
  buffer[size_read] = 0;
  i = 0;
  while (buffer[i] && buffer[i] != ';')
    i += 1;
  tmp = my_little_atoi(buffer + i + 1);
  if (tmp == size && write_line_down(size) == -1)
    return (-1);
  else if (tmp != size)
    if (write(1, str, 4) == -1)
      return (-1);
  return (0);
}
