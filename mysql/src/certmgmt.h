#ifndef CERTMGMT_H
#define CERTMGMT_H

#include <mysql.h>
#include <my_global.h>

#define QUERY_SIZE   128

MYSQL *connectdbs();
int queryrow(MYSQL *mysql,char *mac);
int insertrow(MYSQL *mysql,char *uid,char *tid,char *mac);
int delrow(MYSQL *mysql,char *mac);
int mysql_gettid(unsigned char *EPC);

#endif