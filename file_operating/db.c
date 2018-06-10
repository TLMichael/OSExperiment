#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fd;

void panic(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void db_open(char *path)
{
	mode_t mode = 0777;
	fd = open(path, O_RDWR | O_APPEND | O_CREAT, mode);
	if(fd < 0)
		panic("open");
}

void db_close()
{
	close(fd);
}

struct record {
	char name[12];
	int age;
};

void db_append(char *name, int age)
{
	struct record record;
	strcpy(record.name, name);
	record.age = age;
	
	int count = write(fd, &record, sizeof(struct record));
	if(count < 0)
		panic("write");
}

void db_dump(int index)
{
	int offset = index * sizeof(struct record);
	lseek(fd, offset, SEEK_SET);

	struct record record;
	int count = read(fd, &record, sizeof(struct record));
	if(count != sizeof(struct record))
		panic("read");

	printf("name = %6s, age = %d\n", record.name, record.age);
}

int main()
{
	db_open("my.db");
	db_append("tom", 10);
	db_append("jerry", 11);
	db_append("mike", 12);
	db_dump(2);
	db_dump(1);
	db_dump(0);
	db_close();
	return 0;
}
