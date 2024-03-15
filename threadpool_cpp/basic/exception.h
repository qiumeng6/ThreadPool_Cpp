#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

/**
 * 为exception包装了一层
 * 尽量在库内部使用
 * 重载的what函数中 noexcept 是必须的
 * 参考：https://stackoverflow.com/questions/35763027/looser-throw-specifier-for-virtual-const-char-ro-errstderrwhat-const
*/

namespace thpool {

/** 获取当前代码所在的位置信息 */
#define GET_CODE_LOCATE                                               \
    (std::string(__FILE__) + " | " + std::string(__FUNCTION__)          \
    + " | line = [" + ::std::to_string( __LINE__) + "]")

#define THROW_EXCEPTION(info)                                    \
    throw ExceptionThpool(info, GET_CODE_LOCATE);


class ExceptionThpool : public std::exception{

public:
    explicit ExceptionThpool(const std::string& info, 
                             const std::string& locate = ""){
        info_ = info.empty() ? "ATTENTION ! FIND EXCEPTION!" : info;
    }

    const char* what() const noexcept override {
        return info_.c_str();
    }

private:
    std::string info_ {" "};

};


} // thpool


#endif // EXCEPTION_H