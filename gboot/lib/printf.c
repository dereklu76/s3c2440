#include "vsprintf.h"
#include "uart.h"

int printf(const char *fmt, ...)
{
	va_list args;
	char buf[1024];
	int i = 0;

	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end();

	while(buf[i])
	{
		putc(buf[i++]);
	}

	return i;
}


int scanf(const char *fmt, ...)
{
	va_list args;
	char buf[1024];
	int i = 0;
	char ch;

	while(1)
	{
		ch = getc();

		if((ch == '\n')||(ch == '\r'))
		{
			buf[i] = 0;
			break;
		}
		else
		{
			buf[i++] = ch;
		}
	}

	va_start(args, fmt);
	vsscanf(buf, fmt, args);
	va_end();

	return i;
}


