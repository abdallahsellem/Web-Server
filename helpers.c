#include "definations.h"
#include <arpa/inet.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
//
// Return 1 if static, 0 if dynamic content
// Calculates filename (and cgiargs, for dynamic) from uri
//
int request_parse_uri(char *uri, char *filename, char *cgiargs)
{
	char *ptr;

	if (!strstr(uri, "cgi"))
	{
		// static
		strcpy(cgiargs, "");
		sprintf(filename, ".%s", uri);
		if (uri[strlen(uri) - 1] == '/')
		{
			strcat(filename, "index.html");
		}
		return 1;
	}
	else
	{
		// dynamic
		ptr = index(uri, '?');
		if (ptr)
		{
			strcpy(cgiargs, ptr + 1);
			*ptr = '\0';
		}
		else
		{
			strcpy(cgiargs, "");
		}
		sprintf(filename, ".%s", uri);
		return 0;
	}
}

int get_filesize(int con_fd)
{

	char buf[8192], method[8192], uri[8192], version[8192];
	char filename[8192], cgiargs[8192];
	struct stat s;
	recv(con_fd, buf, sizeof(buf), MSG_PEEK);
	sscanf(buf, "%s %s %s\n", method, uri, version);
	int condi = request_parse_uri(uri, filename, cgiargs);
	printf(" \n filename: %s \n", filename);
	stat(filename, &s);
	printf(" \n file Size inside : %d \n", (int)s.st_size);
	return (int)s.st_size;
}
