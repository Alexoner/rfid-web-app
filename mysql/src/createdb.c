/*************************************************************************
    > File Name: createdb.c
    > Author: onerhao
    > Mail: haodu@hustunique.com
    > Created Time: Fri 23 Aug 2013 12:40:47 AM CST
 ************************************************************************/

#include <my_global.h>
#include <mysql.h>
#include <stdio.h>

int main(int argc,char **argv)
{
	MYSQL *conn=mysql_init(NULL);//initialize
	if(conn==NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}
	if(mysql_real_connect(conn,"127.0.0.1","user12","34klq*",
				NULL,0,NULL,0)==NULL)//connect
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		mysql_close(conn);
		getchar();
		exit(1);
	}

	if(mysql_query(conn,"CREATE DATABASE testdb"))
	{//
		fprintf(stderr,"%s\n",mysql_error(conn));
		mysql_close(conn);
		getchar();
		exit(1);
	}

	mysql_close(conn);
	getchar();
	exit(0);
}
