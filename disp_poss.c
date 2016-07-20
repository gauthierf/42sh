/*
** disp_possible_comp.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:20:41 2016
** Last update Wed Jun  8 10:55:47 2016 
*/

#include <unistd.h>
#include "readline.h"
#include "my.h"

static int	loop_disp_comp(t_completion *list)
{
  while (list)
    {
      if ((my_putstr("\n", 1)) == -1
	  || (my_putstr(list->file, 1)) == -1)
	return (-1);
      list = list->next;
    }
  return (0);
}

static int	ask_continue(int nb)
{
  char		buf;
  int		check;

  if (((my_putstr("\nDisplay all ", 1)) == -1)
      || ((my_putnbr(nb)) == -1)
      || ((my_putstr(" possibilities ? (y or n)", 1)) == -1))
    return (-1);
  while ((check = read(0, &buf, 1)) > 0)
    {
      if (buf == 'y')
	return (1);
      else if (buf == 'n')
	return (0);
    }
  if (check == -1)
    return (-1);
  return (0);
}

int	disp_possible_comp(t_rdd *reader, t_completion *list)
{
  int	check;
  int	size_list;

  check = 1;
  if (list->next == (void*)0)
    return (0);
  if ((size_list = get_size_completition(list)) > 40)
    if ((check = ask_continue(size_list)) == -1)
      return (-1);
  if (check)
    if ((loop_disp_comp(list)) == -1)
      return (-1);
  if ((my_putstr("\n", 1)) == -1)
    return (-1);
  if (reader->prompt)
    if ((my_putstr(reader->prompt, reader->fd)) == -1)
      return (-1);
  if ((disp_list_read(reader->list_read, 1)) == -1)
    return (-1);
  reader->is_completition = 0;
  return (0);
}
