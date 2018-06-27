//´«Êä×Ö·ûÊý×é 

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
int main(){
  int client(char *IP,char * port,char * data,int DATA_LENGTH);
  char *IP ="192.168.4.27";
  char *port ="1234";
  char  data[3000] ;
  int i;
  for ( i=0;i<3000;i++){
		data[i]=68;
	}
  client(IP,port,data,3000);
  return 0;
}
int client(char *IP,char * port,char *data ,int DATA_LENGTH)  
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
    
    int j=0; 
    for(j = 0;j < DATA_LENGTH;){
		int i;
		for( i = 0;i < MAXLINE;i++,j++){
			buf[i]=data[j];
			if(j>=DATA_LENGTH){
				break;
			}
		}
        if(i<=0){
			break;
		}
        read_len = i;
        send_len = send(sock_id, buf, read_len, 0);  
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

