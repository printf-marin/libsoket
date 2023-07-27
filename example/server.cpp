#include<cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <cstring>
#include"socket.h"
#include "tcpsocket.h"
#include "epoll.h"
using namespace my;
#define PORT "4212"
#define SERVER "0.0.0.0"
#define BUFSIZE 1024
struct serverarg{
    TCPServer server;
    Epoll ep;
};

class ClientFunc:public HandleEventOBJ{
    Epoll* ep;
    my::TCPSocket socket;
public:
    ClientFunc(Epoll* ep,my::TCPSocket socket):ep(ep),socket(socket){}
    void handle(epoll_event event){
        if(event.events & EPOLLIN){
            char buf[BUFSIZ];
            int ret = socket.ReadString(buf,BUFSIZE);
            if(ret < 0){
                perror("ReadString");
                return ;
            }
            if(!ret){
                ep->DelEvent(&socket);
                socket.ShutDown(SHUT_RDWR);
                socket.Close();
                return ;
            }
            socket.WriteString("hello world\n",strlen("hello world\n"));
#ifdef MY_DEBUG
            printf("%d:%s\n",socket.FD(),buf);
#endif
            ep->ModifyEvent(&socket,EPOLLIN|EPOLLRDHUP|EPOLLET|EPOLLONESHOT);
            return ;
        }
        if(event.events & (EPOLLRDHUP)){
            printf("有连接断开\n");
            ep->DelEvent(&socket);
            socket.ShutDown(SHUT_RDWR);
            socket.Close();
        }
        return ;
    }
};

class ServerFunc:public HandleEventOBJ{
    Epoll* ep;
    my::TCPServer* server;
    public:
        ServerFunc(Epoll* ep,my::TCPServer* server):ep(ep),server(server){}
    public:
        void handle(epoll_event event){
            struct sockaddr_in raddr;
            socklen_t len = sizeof(raddr);
            auto socket = server->Accept();
            printf("有链接加入：%d\n",socket.FD());
            ep->AddEvenet(&socket,EPOLLIN|EPOLLRDHUP|EPOLLET|EPOLLONESHOT,shared_ptr<HandleEventOBJ>(new ClientFunc(ep,socket)));
        }
};

int main(){
    my::TCPServer server(SERVER,atoi(PORT));
    if(server.Listen() < 0){
        perror("Listen:");
        exit(1);
    }
    my::Epoll ep;
    ep.EventInit();
    auto func = shared_ptr<HandleEventOBJ>(new ServerFunc(&ep,&server));
    ep.AddEvenet(&server,EPOLLIN|EPOLLET,func);
    ep.LoopWait();
}
// 这段代码实现了一个简单的TCP服务器。主要包含以下内容：

// 1. 引入了一些系统头文件和自定义的头文件。

// 2. 定义了宏和常量，包括端口号、服务器地址、缓冲区大小等。

// 3. 定义了一个结构体`serverarg`，包含了一个`TCPServer`对象和一个`Epoll`对象，用于传递给服务器和事件处理函数。

// 4. 定义了一个名为`ClientFunc`的类，继承自`HandleEventOBJ`，用于处理客户端连接的事件。

// 5. 在`ClientFunc`类中，定义了一个`Epoll`指针和一个`TCPSocket`对象，用于保存事件处理函数的上下文。

// 6. 在`ClientFunc`类中，实现了`handle`函数，用于处理客户端连接的事件，包括接收数据、发送数据和处理连接断开等操作。

// 7. 定义了一个名为`ServerFunc`的类，继承自`HandleEventOBJ`，用于处理服务器接受连接的事件。

// 8. 在`ServerFunc`类中，定义了一个`Epoll`指针和一个`TCPServer`指针，用于保存事件处理函数的上下文。

// 9. 在`ServerFunc`类中，实现了`handle`函数，用于处理服务器接受连接的事件，包括接受新的连接并添加到事件监听中。

// 10. 在`main`函数中，创建了一个`TCPServer`对象并调用`Listen`函数进行监听。

// 11. 创建了一个`Epoll`对象，并初始化事件。

// 12. 创建了一个`ServerFunc`对象，并将其作为事件处理函数添加到`Epoll`对象中。

// 13. 调用`LoopWait`函数开始事件循环，等待事件的触发和处理。

// 以上代码的主要逻辑是通过`Epoll`实现多路复用，监听服务器的连接事件和客户端的读写事件，通过不同的事件处理函数来处理不同的事件，以实现TCP服务器的基本功能。