# TCP
TCP
文件传输

1、编译

　　client:gcc -o client client.c

　　server:gcc -o server server.c

2、运行

　　client端：./client IP地址 <端口号> <上传文件名>

　　server端：./server <端口号> <保存为文件名>

其中，server端先运行，client端与server端的端口号必须一致并且不能与已知端口冲突（如可设为1234）。

若只在某一PC的linux系统上进行客户端服务端文件通信测试，需注意：

server IP可设为回送地址127.0.0.1；

可开多个终端来模拟客户端和服务端。
