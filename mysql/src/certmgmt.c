/*************************************************************************
    > File Name: createdb.c
    > Author: onerhao
    > Mail: haodu@hustunique.com
    > Created Time: Fri 23 Aug 2013 12:40:47 AM CST
 ************************************************************************/

#include <my_global.h>
#include <mysql.h>
#include <stdio.h>

#include "certmgmt.h"

MYSQL *connectdbs()
{
	MYSQL *mysql=mysql_init(NULL);
	if(mysql_real_connect(mysql,"127.0.0.1","user12","34klq*",
				"testdb",0,NULL,0)==NULL)
	{
		return NULL;
	}
	return mysql;
}

int queryrow(MYSQL *mysql,char *mac)
{
	MYSQL_RES *result;
	//MYSQL_ROW row;
	char query[QUERY_SIZE];
	//int i=0,field_col=-1;
	strcpy(query,"SELECT  * FROM RFIDTAG WHERE mac=\'");
	strcat(query,mac);
	strcat(query,"\'");

	if(mysql_query(mysql,query))
	{
		return -1;
	}
	result=mysql_store_result(mysql);
	/*while(field=mysql_fetch_field(result))
	{
		if(strcmp(field->name,"uid")==0)
		{
			field=i;
		}
		else
		{
			i++;
		}
	}*/
	if(mysql_num_rows(result)!=1)
		return -1;
	mysql_free_result(result);
	return 0;
}

int insertrow(MYSQL *mysql,char *uid,char *tid,char *mac)
{//insert an entry into the table
	MYSQL_RES *result;
	MYSQL_ROW row;
	char query_string[QUERY_SIZE];
	int i=0,field_col=-1;
	strcpy(query_string,"INSERT INTO diploma VALUES(\'");
	strcat(query_string,tid);
	strcat(query_string,"\',\'");
	strcat(query_string,uid);
	strcat(query_string,"\',\'");
	strcat(query_string,mac);
	strcat(query_string,"\'");

	if(mysql_query(mysql,query_string))
	{
		return 0;
	}
	return 1;
}

int delrow(MYSQL *mysql,char *mac)
{
	char query_string[64];
	strcpy(query_string,"DELETE FROM diploma WHERE mac=\'");
	strcat(query_string,mac);
	strcat(query_string,"\'");

	if(mysql_query(mysql,query_string))
	{
		return 0;
	}
	return 1;
}

