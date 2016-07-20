/*
** source.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:53:36 2016
** Last update Wed Jun  8 10:00:44 2016 
*/

#include <unistd.h>
#include "tools.h"
#include "my.h"

int	my_source(t_mini *shell, t_process *proc)
{
  (void)proc;
  alias(NULL, -1);
  parse_rc_file(shell);
  return (SUCCESS);
}
