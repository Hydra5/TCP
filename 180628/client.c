//传输多个结构体 

#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <time.h> 
//#include<sys/time.h> 
  
#define    MAXLINE        1024  


typedef struct {
	int Nr; // real particles
	int *type;
	//real *radius,*mass;
	//real4 *x,*v,*o; // x.w = radius, v.w = mass, o.w = type
	//real3 *f; // force
	//real3 *t; // torque
	//real4 *ep1;
	//real4 *ep1f; // dirve value of ep1
} t_patic_send;

int client(char *IP,char * port,t_patic_send *data, int n )  
{     
    struct sockaddr_in     serv_addr;  
    char                   buf[MAXLINE];  
    int                    sock_id;  
    int                    read_len;  
    int                    send_len;  
    //FILE                   *fp;  
    int                    i_ret; 
    struct timeval  tv_start,tv_end;
    double  delta_time;

    gettimeofday(&tv_start,NULL);
    
    //if ((fp = fopen(name,"r")) == NULL) 
    //{  
    // perror("Open file failed\n");  
    // exit(0);  
    //}  

      
/*<-----------------------------------------socket---------------------------------------------->*/
    if ((sock_id = socket(AF_INET,SOCK_STREAM,0)) < 0) {  
        perror("Create socket failed\n");  
        exit(0);  
    }  
/*<-----------------------------------------connect---------------------------------------------->*/
    memset(&serv_addr, 0, sizeof(serv_addr));  
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(atoi(port));  
    inet_pton(AF_INET, IP, &serv_addr.sin_addr);  
     
    i_ret = connect(sock_id, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));  
    if (-1 == i_ret) 
    {  
        printf("Connect socket failed\n");  
       return -1;  
    }  
/*<-------------------------------------client send part---------------------------------->*/ 
    bzero(buf, MAXLINE);
	int j = 0;
	for(j = 0;j < n;){	
		int i;
		for(i = 0;i < (MAXLINE/sizeof(t_patic_send));i++,j++){
			memcpy(buf+i,data+j,sizeof(t_patic_send)); 
			if(j >= n){break;}
		}
		send_len = send(sock_id,buf,sizeof(t_patic_send)*i,0);
		if ( send_len < 0 ) 
		{  
			perror("Send file failed\n");  
			exit(0);  
		} 
		bzero(buf, MAXLINE);
	}		
  
    // fclose(fp);  
    close(sock_id);
    
    gettimeofday(&tv_end,NULL);
    delta_time = 1000.*(tv_end.tv_sec-tv_start.tv_sec)+(tv_end.tv_usec-tv_start.tv_usec)/1000;
    printf("time:%.10f\n",delta_time);
    printf("Send Finish\n");  
    return 0;  
}  
int main(){
  char *IP ="192.168.4.27";
  char *port ="1234";
  t_patic_send  data[100];
  int i = 0;
  for(;i<100;i++){
	  data[i].Nr=i;
	  data[i]->type=i;
  }
  int n = 100;
  client(IP,port,data,n);
  return 0;
}
