#include "head.h"

int main(void) {
	int fd;
	char buf[MAXSIZE]; 

	if (!check_fifo_exist())
		if (mk_fifo() == -1) {
			printf("创建FIFO文件出错");
			perror("mkfifo");
		}
	
	if ((fd = open(FILE_PATH, O_WRONLY)) == -1) {
		printf("打开FIFO文件出错");
		perror("open");
	}

	while(1) {
		printf("send msg: ");
		fgets(buf, MAXSIZE, stdin);
		write(fd, buf, strlen(buf));
		if (strcmp("exit\n", buf) == 0)
			break;
	}

	close(fd);
	if (check_fifo_exist())
		if (rm_fifo() == -1) {
			printf("删除FIFO文件出错");
			perror("rmfifo");
		}

    return 0;
}
