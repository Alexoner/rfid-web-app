#ifndef READER_H
#define READER_H


int parse_argument(char *request);
char *get_argument();
int scan();
int readmac(char *epc);
int verify(char *mac);


#endif