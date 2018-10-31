# socket
网络程序是由两个部分组成的--客户端和服务器端.它们的建立步骤一般是: 

服务器端 
socket-->bind-->listen-->accept 

客户端 
socket-->connect



编译产生两个程序server.o(服务器端)和client.o(客户端) 
先运行./server.o portnumber& (portnumber随便取一个大于1204且不在/etc/services中出现的号码 就用8888好了),然后运行 ./client.o localhost 8888 
