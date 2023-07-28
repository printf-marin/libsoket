#include<httpfile.h>
#include<cstring>
using namespace my;

MYLIBSOCKET_DEFINE_CLASS(MultipartFile,std::string,name,std::string,filename,size_t,size,std::string,ContentType,DistpositionType,dispostionType)

MultipartFile::MultipartFile():name(""),filename(""),size(0),content(nullptr),ContentType(""),dispostionType("form-data"){}

MultipartFile::~MultipartFile(){
    if(content){
        delete content;
    }
}

MultipartFile::MultipartFile(const MultipartFile& other):name(other.name),filename(other.filename),size(other.size),\
                            ContentType(other.ContentType),dispostionType(other.dispostionType){
    if(other.content){
        content = new byte_t[size]();
        memcpy(content,other.content,size);
    }
}

MultipartFile& MultipartFile::operator=(const MultipartFile& other){
    name = other.name;
    filename = other.filename;
    size = other.size;
    ContentType = other.ContentType;
    dispostionType = other.dispostionType;
    if(content){
        delete []content;
    }
    if(other.content){
        content = new byte_t[size]();
        memcpy(content,other.content,size);
    }
    return *this;
}

void MultipartFile::SetContent(const byte_t* content,const size_t& size){
    this->content = new byte_t[size];
    memcpy(this->content,content,size);
    return ;
}
byte_t* MultipartFile::GetContent() const{
    return content;
}
// 这段代码是一个文件上传类MultipartFile的实现。首先包含了一些头文件，然后使用了命名空间my。

// 接下来使用宏定义MYLIBSOCKET_DEFINE_CLASS定义了MultipartFile类，这个类有五个成员变量：name、filename、size、ContentType和dispostionType，分别表示文件的名称、文件名、文件大小、内容类型和分部类型。

// MultipartFile类有一个默认构造函数，初始化成员变量为默认值。还有一个析构函数，如果content不为空，则释放content的内存。

// 类中还有一个拷贝构造函数和一个赋值运算符重载函数，用于实现深拷贝。拷贝构造函数会创建一个新的content数组，并将other的content数组内容复制到新的content数组中。赋值运算符重载函数会先释放原有的content内存，然后创建一个新的content数组，并将other的content数组内容复制到新的content数组中。

// 类中还有两个成员函数SetContent和GetContent，分别用于设置和获取content的值。SetContent函数会先释放原有的content内存，然后创建一个新的content数组，并将传入的content数组内容复制到新的content数组中。GetContent函数用于返回content的指针。

// 总结起来，这段代码实现了一个文件上传类MultipartFile，提供了设置和获取文件内容的功能，并且实现了深拷贝和内存管理。
