/*************************************************************************
    > File Name: data.c
    > Author: onerhao
    > Mail: haodu@hustunique.com
    > Created Time: Thu 22 Aug 2013 09:37:51 PM CST
 ************************************************************************/

#include <my_global.h>
#include <mysql.h>

int print_version()
{
	printf("MySQL client version: %s\n",mysql_get_client_info());
	return 0;
}

int main(int argc,char **argv)
{
	print_version();
	return 0;
}
