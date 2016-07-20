/*
** manage_signal.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:20:51 2016
** Last update Wed Jun  8 10:28:40 2016 
*/

#include "readline.h"
#include "my.h"

int			manage_signal(int is_signal, t_rdd *reader)
{
  static t_rdd		*ptr;

  if (is_signal == 0)
    ptr = reader;
  else if (ptr)
    {
      ptr->list_read = (void*)0;
      ptr->current = 0;
      ptr->is_rm = 0;
      ptr->is_completition = 0;
      if (ptr->prompt)
	{
	  if ((my_putstr("\n", 1)) == -1)
	    return (-1);
	  if ((my_putstr(ptr->prompt, 1)) == -1)
	    return (-1);
	}
    }
  else
    if ((my_putstr("\n$> ", 1)) == -1)
      return (-1);
  return (0);
}

void	get_sigint(int signal)
{
  (void)signal;
  manage_signal(1, (void*)0);
}
