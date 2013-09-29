/*************************************************************************
    > File Name: retrieve_img.c
    > Author: onerhao
    > Mail: haodu@hustunique.com
    > Created Time: Fri 23 Aug 2013 03:36:15 PM CST
 ************************************************************************/

#include <mysql.h>
#include <my_global.h>

void finish_with_error(MYSQL *con)
{
	fprintf(stderr,"%s\n",mysql_error(con));
	mysql_close(con);
	exit(1);
}

int main(int argc,char **argv)
{
	FILE *fp=fopen("lena2.jpg","wb");
	if(fp==NULL)
	{
		perror("fopen");
		exit(1);
	}

	MYSQL *con=mysql_init(NULL);

	if(con==NULL)
	{
		perror("mysql_init()");
		exit(1);
	}

	if(mysql_real_connect(con,"127.0.0.1","user12","34klq*",
				"testdb",0,NULL,0)==NULL)
	{
		finish_with_error(con);
	}
	if(mysql_query(con,"SELECT Data FROM Images WHERE Id=1"))
	{
		finish_with_error(con);
	}
	MYSQL_RES *result=mysql_store_result(con);

	if(result==NULL)
	{
		finish_with_error(con);
	}

	MYSQL_ROW row=mysql_fetch_row(result);
	unsigned long *lengths=mysql_fetch_lengths(result);

	if(lengths==NULL)
	{
		finish_with_error(con);
	}

	fwrite(row[0],lengths[0],1,fp);

	if(ferror(fp))
	{
		fprintf(stderr,"fwrite() failed\n");
		mysql_free_result(result);
		mysql_close(con);
		exit(1);
	}

	fclose(fp);

	mysql_free_result(result);
	mysql_close(con);
	return 0;
}
