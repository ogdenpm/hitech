/*
 * vfprintf - formatted output without ellipsis
 */

#include	<stdio.h>
#include	<stdarg.h>

extern int	_doprnt();

int
vfprintf(FILE *	file, char * fmt, va_list args) {
	return _doprnt(file, fmt, args);
}


