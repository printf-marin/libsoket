#include<tcpsocket.h>
#include "cstring"
#define PORT   "4212"
#define SERVER "127.0.0.1"
using namespace my;
int main(){
    TCPClient client(SERVER,atoi(PORT));
    client.Connection();
    client.WriteString("hello,world\n",strlen("hello,world"));
    char buff[1024] ="";
    client.ReadString(buff,1024);
    printf("%s\n",buff);
    client.ShutDown(SHUT_RDWR);
    client.Close();
}
// 这段代码使用了名为`TCPClient`的类来与服务器建立TCP连接并进行通信。下面是对代码的解释：

// 1. `#include<tcpsocket.h>`：包含了名为`tcpsocket.h`的头文件，该头文件中定义了TCPSocket相关的类和函数。

// 2. `#include "cstring"`：包含了cstring头文件，用于使用字符串相关的函数。

// 3. `#define PORT   "4212"`：定义了一个常量 `PORT`，表示服务器的端口号。

// 4. `#define SERVER "127.0.0.1"`：定义了一个常量 `SERVER`，表示服务器的IP地址。

// 5. `using namespace my;`：使用命名空间 `my`，该命名空间可能包含了所需的`TCPClient`类。

// 6. `int main()`：程序的主函数。

// 7. `TCPClient client(SERVER, atoi(PORT));`：创建一个名为 `client` 的`TCPClient`对象，传入服务器的IP地址和端口号作为参数。`atoi()`函数用于将字符串转换为整数。

// 8. `client.Connection();`：调用`TCPClient`对象的`Connection()`方法，即与服务器建立TCP连接。

// 9. `client.WriteString("hello,world\n",strlen("hello,world"));`：向服务器发送字符串 "hello,world\n"。`WriteString()`方法用于发送数据到服务器，第一个参数是要发送的字符串，第二个参数是字符串的长度。

// 10. `char buff[1024] ="";`：创建一个大小为1024字节的字符数组 `buff`，用于接收从服务器返回的数据。

// 11. `client.ReadString(buff,1024);`：从服务器读取数据，将数据存储到`buff`数组中。`ReadString()`方法用于从服务器接收数据，第一个参数是接收数据的缓冲区，第二个参数是缓冲区的长度。

// 12. `printf("%s\n",buff);`：将从服务器接收到的数据打印出来，使用 `printf()` 函数。

// 13. `client.ShutDown(SHUT_RDWR);`：关闭与服务器的连接，使用 `ShutDown()` 方法，参数 `SHUT_RDWR` 表示同时关闭读取和写入操作。

// 14. `client.Close();`：关闭客户端的连接，使用 `Close()` 方法。

// 以上代码实现了一个TCP客户端，通过建立连接与服务器进行通信。首先创建一个`TCPClient`对象，并使用`Connection()`方法与服务器建立连接。然后使用`WriteString()`方法发送字符串到服务器，再使用`ReadString()`方法接收从服务器返回的数据，并存储到`buff`数组中。最后关闭连接，释放资源。