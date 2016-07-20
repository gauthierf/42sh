/*
** my_printf.h for  in /home/fernan_w/Téléchargements/42sh/includes
** 
** Made by 
** Login   <fernan_w@epitech.net>
** 
** Started on  Thu Jun  2 23:23:48 2016 
** Last update Sun Jun  5 22:19:06 2016 
*/

#ifndef MY_PRINTF_H_
# define MY_PRINTF_H_

int	count_prints();
int	my_count_putchar(char, int);
int	my_count_putstr(char *, int);
int	my_count_putnbr_base(unsigned int, char *, int);
int	chop_chop_count(unsigned int, int, char *, int);
int	my_count_put_nbr(int, int);
int	my_print_error(const char *, ...);
int	my_printf(const char *, ...);
int	my_put_hex(unsigned int, char, int);
int	my_put_ptr(unsigned int, int);
int	my_putstr_weird(char *, int);
int	my_put_unsigned_nbr(unsigned int, int);
int	print_modified_count(char, int);

#endif /* !MY_PRINTF_H_ */
