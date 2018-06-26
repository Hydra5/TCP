
   #include <time.h> 
   
   int main(int argc,char **argv)  
   {     
      struct timeval  tv_start,tv_end;
      double  delta_time;
      gettimeofday(&tv_start,NULL);
    
       //程序
   
       gettimeofday(&tv_end,NULL);
       delta_time = 1000.*(tv_end.tv_sec-tv_start.tv_sec)+(tv_end.tv_usec-tv_start.tv_usec)/1000;
      printf("time:%.10f\n",delta_time);
      return 0;  
   } 

