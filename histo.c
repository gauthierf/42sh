/*
** disp_historic.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:20:02 2016
** Last update Wed Jun  8 10:47:11 2016 
*/

#include "readline.h"
#include "my.h"

int	disp_historic(t_histo *historic)
{
  if (!(historic))
    return (0);
  while (historic && historic->next)
    historic =  historic->next;
  if (historic && historic->prev)
    if ((my_putstr("-> ", 1)) == -1)
      return (-1);
  while (historic && historic->prev)
    {
      if ((disp_list_read(historic->list_read, 1)) == -1)
	return (-1);
      if ((my_putstr("\n", 1)) == -1)
	return (-1);
      historic = historic->prev;
      if (historic->prev)
	if ((my_putstr("-> ", 1)) == -1)
	  return (-1);
    }
  return (0);
}
