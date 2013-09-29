
DBCFLAGS=`/usr/local/mysql/bin/mysql_config --cflags --libs`

reader:reader.c
	$(CC) -o $@ $^ $(CFLAGS)
data:data.c
	$(CC) -o $@ $^ $(DBCFLAGS)

