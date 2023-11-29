#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <time.h>
int main(){
srand(time(NULL));
mqd_t mqID;
mqID = mq_open("/testmQueue1", O_RDWR | O_CREAT | O_EXCL, 0666,NULL);
	if (mqID < 0){
		if (errno == EEXIST){
			mq_unlink("/testmQueue");
			mqID = mq_open("/testmQueue1", O_RDWR | O_CREAT, 0666,NULL);
		}
		else{
			perror("open message queue error...");
			return -1;
		}
	}
	
	for (int i = 1; i <= 5; ++i){
	int num = (rand() % 100) + 1;	
	char msg[4];
	sprintf(msg, "%d", num);
		if (mq_send(mqID, msg, sizeof(msg), i) < 0){
			printf("send message %d failed \n", i);
		}
	printf("send message %d success \n",i); 
	sleep(1);
}
	
	if (fork() == 0){
		struct mq_attr mqAttr;
		mq_getattr(mqID, &mqAttr);
		
		int sum = 0;
		int prod = 1;
		char buf[mqAttr.mq_msgsize];
		for (int i = 1; i <= 5; ++i){
			if (mq_receive(mqID, buf, mqAttr.mq_msgsize, NULL) < 0){
				printf("receive message failed... \n");
				perror("error info ");
				continue;
			}
			printf("receive message %d: %s\n",i, buf); 
			sum += atoi(buf);
			prod *= atoi(buf);
		}
		printf("sum of nums %d\n",sum);
		printf("prod of nums %d\n",prod); 
		exit(0);
	}


}

