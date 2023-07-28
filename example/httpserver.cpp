#include<iostream>
#include<http.h>
#include<httpengine.h>
#include<resptype.h>
#include<unistd.h>
using namespace my;

MYLIBSOCKET_DECL_JSON_CLASS_HEAD(Resp,int,code,string,msg)
MYLIBSOCKET_DECL_CLASS_END

MYLIBSOCKET_DEFINE_CLASS(Resp,int,code,string,msg)
MYLIBSOCKET_DEFINE_JSON_SERIALIZATION(Resp,code,msg)

//声明一个类
MYLIBSOCKET_DECL_JSON_CLASS_HEAD(LoginReq,string,username,string,password,string,salt,bool,login)
public:
    bool CheckLogin();
MYLIBSOCKET_DECL_CLASS_END

// 定义一个类 主要是实现GET和SET方法
MYLIBSOCKET_DEFINE_CLASS(LoginReq,string,username,string,password,string,salt,bool,login)
// 实现ToJson和To
MYLIBSOCKET_DEFINE_JSON_SERIALIZATION(LoginReq,username,password)


bool LoginReq::CheckLogin(){
    if(this->username == "admin" && this->password == "123456"){
        return true;
    }
    return false;
}

void InitRouter(HttpEngine* engine){
    engine->Post("/api/upfile/",[](HttpConn* conn){
        auto files = conn->PostFrom("file");
        Resp resp;
        resp.Setcode(0);
        resp.Setmsg("上传文件测试");
        for(auto file:files){
            int ret = conn->SaveUploadFile(file,"./file/" + file->Getfilename());
        }
        conn->WriteToJson(HttpStatus::StatusOK,&resp);
    });
    engine->Post("/login",[](HttpConn* conn){
        LoginReq req;
        Resp resp;
        conn->BindJsonBody(&req);
        if(!req.CheckLogin()){
            resp.Setcode(200);
            resp.Setmsg("账号或密码错误");
            conn->WriteToJson(HttpStatus::StatusOK,&resp);
        }else{
            conn->WriteToJson(HttpStatus::StatusOK,&req);
        }
    });
    
    engine->Get("/ping",[](HttpConn* conn){
        conn->WriteToJson(HttpStatus::StatusOK,"{\n\
            \"code\":0,\n\
            \"msg\":\"pong\"\n\
        }");
    });



    engine->StaticFile("/static/","../static/"); // 参数一：路由，参数而：文件路径
    engine->NoRouter([](HttpConn* conn){
        Resp resp;
        resp.Setcode(404);
        resp.Setmsg("页面不存在");
        conn->WriteToJson(HttpStatus::StatusNotFound,&resp);
    });
}

int main(){
    pid_t pid = getpid();
    cout<<pid<<endl;
    HttpEngine engine(4490);
    InitRouter(&engine); //初始化路由
    vector<RouterNode> routers;
    engine.GetAllRouter(routers);
    for(auto router:routers){
        cout<<router.method<<":"<<router.url<<endl;
    }
    engine.SetMode(HttpMode::M_Debug);
    engine.Run(); // 监听端口
    return 0;
}
// 这段代码是一个使用C++编写的HTTP服务器。它使用了一些库文件来实现HTTP请求和响应的处理。

// 首先，代码包含了一些标准C++库的头文件，如iostream和unistd.h。然后，它引入了一些自定义的库文件，如http.h和httpengine.h。

// 接下来，代码定义了一个名为Resp的类，它有三个成员变量：整型的code、字符串型的msg和字符串型的msg。这个类还实现了与JSON序列化相关的方法。

// 然后，代码又定义了一个名为LoginReq的类，它有四个成员变量：三个字符串型的username、password、salt和一个布尔型的login。该类还有一个成员函数CheckLogin()，用于检查登录是否成功。

// 在代码的后面，有一个名为InitRouter()的函数，它用于初始化HTTP路由。其中定义了一些路由规则，如处理上传文件、登录和响应ping请求。还定义了一个静态文件的路由。

// 最后，在main()函数中，创建了一个HttpEngine对象，并通过InitRouter()函数初始化了路由。然后，输出了所有的路由信息，并设置了服务器的运行模式为调试模式。最后，调用Run()函数开始监听指定端口的HTTP请求。
