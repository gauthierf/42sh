/*
** about_var.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:56:19 2016
** Last update Sun Jun  5 19:56:29 2016 retyt
*/

#include "my.h"

void	count_var(char *str, int *i)
{
  int		j;

  j = *i + 1;
  while (str[j] && str[j + 1] && str[j] != ')')
    {
      if (str[j] == '$' && str[j + 1] == '(')
	count_var(str, &j);
      else
	j += 1;
    }
  *i = j + 1;
}

void	count_quote(char *str, int *i)
{
  int		j;

  j = *i + 1;
  while (str[j] && str[j] != '`')
    j += 1;
  *i = j + 1;
}

static void	count_little_quote(char *str, int *i)
{
  int		j;

  j = *i + 1;
  while (str[j] && str[j] != '\'')
    j += 1;
  *i = j + 1;
}

static void	count_normal_quote(char *str, int *i)
{
  int		j;

  j = *i + 1;
  while (str[j] && str[j] != '"')
    j += 1;
  *i = j + 1;
}

void	pass_var(char *str, int *i)
{
  if (str[*i] == '$' && str[*i + 1] == '(')
    count_var(str, i);
  else if (str[*i] == '`')
    count_quote(str, i);
  else if (str[*i] == '\'')
    count_little_quote(str, i);
  else if (str[*i] == '"')
    count_normal_quote(str, i);
}
