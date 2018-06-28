#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
  
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
 
int server(char *port,t_patic_send *data, int n)   
{  
    struct sockaddr_in     serv_addr;  
    struct sockaddr_in     clie_addr;  
    char                   buf[MAXLINE];  
    int                    sock_id;  
    int                    link_id;  
    int                    recv_len;  
    int                    write_leng;  
    int                    clie_addr_len;  
  
/*<------------socket----------->*/
    if ((sock_id = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		
        perror("Create socket failed\n");  
        exit(0);  
    }  
/*<------------bind----------->*/
    memset(&serv_addr, 0, sizeof(serv_addr));  
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(atoi(port));  
	//转换成网络数据格式,port为端口号 
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
    if (bind(sock_id, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ) {  
	
        perror("Bind socket failed\n"); 
		//为socket()函数创建的套接字关联一个相应地址
        exit(0);  
    }  
/*<-----------listen------------>*/
    if (-1 == listen(sock_id, 10)) {
		
        perror("Listen socket failed\n");  
        exit(0);  
    }  
/*<----------server receive part---------->*/
    while (1) { 
	
        clie_addr_len = sizeof(clie_addr); 
/*<----------------accept--------------->*/        
        link_id = accept(sock_id, (struct sockaddr *)&clie_addr, &clie_addr_len);  
        
		if (-1 == link_id) {		
            perror("Accept socket failed\n");  
            exit(0);  
        }
		
        bzero(buf, MAXLINE);
		int j = 0;
        while (recv_len = recv(link_id, buf, MAXLINE, 0)){
			
            if(recv_len < 0) {  
                printf("Recieve Data From Server Failed!\n");  
                break;  
            }  
            printf("#");
			int i;
			for(i = 0;i < (recv_len/sizeof(t_patic_send));i++，j++){
				if(j >n){
					data = (t_patic_send*)realloc(data,sizeof(t_patic_send)*(j));
				}
				memcpy(data+j,buf+i,sizeof(t_patic_send)); 
			}

            bzero(buf,MAXLINE);  
        }
		n = j;
        printf("\nFinish Recieve\n");  
        close(link_id);  
    }  
    close(sock_id);   
    return 0;  
}  

int main(){
	char *port ="1234";
	t_patic_send  *data;
	int n = 100;
	data = (t_patic_send*)malloc(sizeof(t_patic_send)*n);
	server(port,data,&n);
	return 0;
}
