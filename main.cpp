#include <stdio.h>
#include <iostream>
#include <my_global.h>
#include "uhf\CommandLib.h"
#include "web\reader.h"
#include "query.h"

#define DEBUG 0

int main()
{
#if DEBUG
	parse_argument("action=read&tag_epc=E20494546478545324401C10");
	getchar();
#else
	char *request=NULL;
	printf("Content-type; text/plain\n\n");
	request=get_argument();
	parse_argument(request);
#endif
	return 0;
}