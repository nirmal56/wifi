#include <functional>
#include <iostream>
#include <string>

class RedundencyManager // incl. Typo ;-)
{
public:
    // std::function<return_type(list of argument_type(s))>
    std::string Init(std::function<std::string(void)> f)
    {
        return f();
    }
    std::function<void(const std::string mydata)> fun;

};

class CLoggersInfra
{
private:
    std::string member = "Hello from non static member callback!";

public:
    static std::string RedundencyManagerCallBack()
    {
        return "Hello from static member callback!";
    }

    std::string NonStaticRedundencyManagerCallBack()
    {
        return member;
    }

    std::string withargument(std::string &mydata)
    {
        return mydata;
    }
};

std::string NonMemberCallBack()
{
    return "Hello from non member function!";
}

int main()
{
    auto instance = RedundencyManager();

    auto callback1 = std::bind(&NonMemberCallBack);
    std::cout << instance.Init(callback1) << "\n";

    // Similar to non member function.
    auto callback2 = std::bind(&CLoggersInfra::RedundencyManagerCallBack);
    std::cout << instance.Init(callback2) << "\n";

    // Class instance is passed to std::bind as second argument.
    // (heed that I call the constructor of CLoggersInfra)
    auto callback3 = std::bind(&CLoggersInfra::NonStaticRedundencyManagerCallBack, CLoggersInfra());
    std::cout << instance.Init(callback3) << "\n";

    RedundencyManager redobj;
    const std::string mydata = "mydata from arguments\n";

    auto callback4 = std::bind(&CLoggersInfra::withargument, CLoggersInfra());
    // std::cout<<redobj.Init1(callback4("abc")) << "\n";

}