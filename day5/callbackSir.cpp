#include <functional>
#include <iostream>
#include <string>

class RedundencyManager // incl. Typo ;-)
{

    using FsEventCallabck = std::function<std::string(int data)>;
    using callback2 = std::function<std::string(int tada, int taadaa)>;
    using callback3 = std::function<void(std::string a,std::string b,std::string c,std::string d,std::string e)>;

public:
    // std::function<return_type(list of argument_type(s))>
    std::string Init(FsEventCallabck f, int data)
    {
        return f(data);
    }
    std::string Init(callback2 f, int data, int tada)
    {
        return f(data, tada);
    }
    void Init(callback3 f,std::string a,std::string b,std::string c,std::string d,std::string e)
    {
        return f(a,b,c,d,e);
    }
};

class CLoggersInfra
{
private:
    std::string member = "Hello from non static member callback!";

public:
    void fiveargfun(std::string a,std::string b,std::string c,std::string d,std::string e){
        std::cout << a << " " << b << " " << c << " " << d << " " << e << "\n"; 
        // return a + " " + b + " " + c + " " + d + " " + e ; 
    }

    static std::string RedundencyManagerCallBack(int data)
    {
        return "Hello from static member callback! " + std::to_string(data);
    }

    std::string NonStaticRedundencyManagerCallBack(int data)
    {
        return member + " " + std::to_string(data);
    }
    std::string twoargfun(int data, int dataa)
    {
        return member + " " + std::to_string(dataa) + " " + std::to_string(data);
    }
};

std::string NonMemberCallBack(int data)
{
    return "Hello from non member function! " + std::to_string(data);
}

int main()
{
    auto instance = RedundencyManager();

    auto callback1 = std::bind(&NonMemberCallBack, std::placeholders::_1);
    std::cout << instance.Init(callback1, 1) << "\n";

    // Similar to non member function.
    auto callback2 = std::bind(&CLoggersInfra::RedundencyManagerCallBack, std::placeholders::_1);
    std::cout << instance.Init(callback2, 2) << "\n";

    // Class instance is passed to std::bind as second argument.
    // (heed that I call the constructor of CLoggersInfra)

    auto callback = std::bind(&CLoggersInfra::NonStaticRedundencyManagerCallBack,CLoggersInfra(),std::placeholders::_1);
    std::cout<<instance.Init(callback,5)<<"\n";

    // auto callback3 = std::bind(&CLoggersInfra::twoargfun, CLoggersInfra(), std::placeholders::_2, std::placeholders::_1);
    // std::cout << instance.Init(callback3, 1, 2) << "\n";

    auto callback5 =std::bind(&CLoggersInfra::fiveargfun,CLoggersInfra(),
                                                        std::placeholders::_1,
                                                        std::placeholders::_2,
                                                        std::placeholders::_3,
                                                        std::placeholders::_4,
                                                        std::placeholders::_5);
    instance.Init(callback5,"this","is","data","to","printed");
}