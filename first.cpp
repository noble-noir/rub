#include <iostream>

class String 
{
    char *data;
    void String_good(char *s)
    {
        if(!s)
        {
            std::cout << "error" << std::endl;
            abort();
        }
    }
    size_t s_len(const char *s)
    {
        size_t len = 0;
        for(; s[len] != '\0'; len++){}
        return len;
    }
public:
    String()
    {
        data = new char[1];
        String_good(data);
        data[0] = '\0';
    }
    String(const char *x)
    {
        size_t len = s_len(x);
        data = new char[len+1];
        String_good(data);
        std::copy(x, x+len, data);
    }
    String(const String &x)
    {
        size_t len = s_len(x.data);
        data = new char[len+1];
        std::copy(x.data, x.data+len, data);
    }
    String &operator=(const String &x)
    {
        if (this != &x)
        {
            delete[] data;
            size_t len = s_len(x.data);
            data = new char[len+1];
            String_good(data);
            std::copy(x.data, x.data+len, data);
        }
        return *this;
    }
    // ~String()
    // {
    //     delete[] data;
    // }
    operator const char* () const 
    {
        return data;
    }
    String operator+(const String &str)
    {
        String res;
        size_t data_len = s_len(data), str_len = s_len(str.data);
        res.data = new char[data_len+str_len+1];
        String_good(res.data);
        for(size_t i = 0; i < data_len; i++)
            res.data[i] = data[i];
        for(size_t i = data_len; i < data_len+str_len+1; i++)
            res.data[i] = str.data[i-data_len];
        return res;
    }
    String operator+=(const String& str)
    {
        String tmp;
        size_t data_len = s_len(data), str_len = s_len(str.data);
        tmp.data = new char[data_len+str_len+1];
        tmp = (*this)+str;
        (*this) = tmp;
        //delete[] tmp.data;
        return *this;
    }
};

int main()
{
    String a{};
    std::cout << (const char*)a << std::endl;
    String b{"abcd\0"};
    std::cout << (const char*)b << std::endl;
    String c = b;
    std::cout << (const char*)c << std::endl;
    b = c+c;
    std::cout << (const char*)b << std::endl;
    b += c;
    std::cout << (const char*)b << std::endl;

    // a.~String();
    // b.~String();
    // c.~String();
    return 0;
}