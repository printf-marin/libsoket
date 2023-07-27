#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <util.h>
#include <cstdio>
#include <socktype.h>
#include <cstring>
#include <limits>
namespace my{

std::string toHex(unsigned char c) {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    return ss.str();
}

int SplitString(const std::string str,const std::string tag,std::vector<std::string>& splite){
        splite.clear(); // 清空 splite 向量

        if (str.empty()) {
            return 0;
        }

        size_t pos = 0;
        size_t len = str.length();
        size_t tagLen = tag.length();
        if(str.substr(0,tagLen) == tag){
            pos = tagLen;
        }
        while (pos < len) {
            size_t found = str.find(tag, pos);

            if (found == std::string::npos) {
                // 如果没找到分隔符，说明当前是最后一个子串
                splite.push_back(str.substr(pos, len - pos));
                break;
            }

            // 如果找到了分隔符，说明当前子串是从 pos 到 found 的子串
            splite.push_back(str.substr(pos, found - pos));

            // 跳过分隔符
            pos = found + tagLen;
        }

        return splite.size();
    }

size_t FindBinary(const byte_t* src_data, const size_t offset, const size_t srcSize, const byte_t* des_data, size_t cmpsize) {
    if (src_data == nullptr || des_data == nullptr || cmpsize > srcSize - offset) {
        return std::numeric_limits<size_t>::max();// 返回错误标识
    }

    const byte_t* start = src_data + offset;
    const byte_t* end = src_data + srcSize - cmpsize + 1;

    for (const byte_t* p = start; p != end; ++p) {
        if (std::memcmp(p, des_data, cmpsize) == 0) {
            return p - src_data; // 找到了，返回下标
        }
    }

    return std::numeric_limits<size_t>::max(); // 没有找到，返回错误标识
}

std::string URLdecode(std::string url){
    std::string result;
    char c;
    int i, len = url.length();
    for (i = 0; i < len; i++) {
        switch (url[i]) {
            case '+':
                result += ' ';
                break;
            case '%':
                if (i + 2 < len && isxdigit(url[i + 1]) && isxdigit(url[i + 2])) {
                    sscanf(url.substr(i + 1, 2).c_str(), "%x", (unsigned int*)&c);
                    result += c;
                    i += 2;
                }
                else {
                    result += '%';
                }
                break;
            default:
                result += url[i];
                break;
        }
    }
    return result;
}

std::string URLencode(std::string url){
    std::string result;
    int i, len = url.length();
    for (i = 0; i < len; i++) {
        switch (url[i]) {
            case ' ':
                result += '+';
                break;
            case '-':
            case '_':
            case '.':
            case '!':
            case '~':
            case '*':
            case '\'':
            case '(':
            case ')':
                result += url[i];
                break;
            default:
                if (isalnum(url[i])) {
                    result += url[i];
                }
                else {
                    result += '%';
                    for (auto c : toHex(url[i]))
                        result += c;
                }
                break;
        }
    }
    return result;
}
};


// 这段代码定义了一个名为`my`的命名空间，并在其中实现了一些通用的工具函数。

// 1. 引入了一些头文件，包括`iostream`、`sstream`、`iomanip`、`string`等。

// 2. `toHex`函数用于将一个无符号字符转换为两位的十六进制字符串。首先创建一个`stringstream`对象，使用`std::hex`设置流的输出格式为十六进制，使用`std::setw`和`std::setfill`设置输出宽度和填充字符，然后将字符转换为整数并输出到流中，最后将流的内容转换为字符串并返回。

// 3. `SplitString`函数用于将一个字符串按照指定的分隔符进行拆分，并将拆分后的子串存储到一个向量中。首先清空向量`splite`，然后遍历字符串，使用`std::string::find`函数找到分隔符的位置，如果找不到分隔符，则将剩余部分作为最后一个子串，如果找到了分隔符，则将分隔符前的部分作为一个子串，并更新`pos`的值。最后返回拆分后的子串数量。

// 4. `FindBinary`函数用于在一个字节数组中查找另一个字节数组，并返回第一次出现的位置。首先判断输入参数的有效性，然后定义一个起始指针`start`和一个结束指针`end`，遍历字节数组，使用`std::memcmp`函数比较当前位置和目标数组的内容，如果相等，则返回当前位置相对于源数组的偏移量。如果遍历结束仍未找到匹配的内容，则返回一个特殊的错误标识。

// 5. `URLdecode`函数用于将一个URL编码的字符串解码为普通字符串。首先创建一个空字符串`result`，然后遍历URL字符串，根据字符的不同情况进行处理：如果是`+`，则将其替换为空格；如果是`%`，则判断后面两个字符是否是十六进制数，如果是，则将其转换为对应的字符；否则，将`%`添加到结果字符串中；其他情况下，直接将字符添加到结果字符串中。最后返回解码后的字符串。

// 6. `URLencode`函数用于将一个普通字符串编码为URL编码的字符串。首先创建一个空字符串`result`，然后遍历输入字符串，根据字符的不同情况进行处理：如果是空格，则将其替换为`+`；如果是特殊字符（包括`-`、`_`、`.`、`!`、`~`、`*`、`'`、`(`、`)`），则直接将其添加到结果字符串中；如果是字母或数字，则直接将其添加到结果字符串中；其他情况下，将字符转换为对应的十六进制字符串，并添加到结果字符串中。最后返回编码后的字符串。

// 总体来说，这段代码实现了一些通用的工具函数，用于处理字符串和字节数组的转换、拆分和查找等操作。这些函数可以在HTTP库中用于处理URL编码、字符串拆分和字节数组查找等功能。