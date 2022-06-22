#include <functional>
#include <iostream>
#include <string>

using Callabck = std::function<std::string(int data)>;
class RedundencyManager // incl. Typo ;-)
{
public:
    // std::function<return_type(list of argument_type(s))>
    std::string Init(Callabck f, int data)
    {
        return f(data);
    }
    std::function<void(const std::string mydata)> fun;

};

class CLoggersInfra
{
private:
    std::string member = "Hello from non static member callback!";

public:
    static std::string RedundencyManagerCallBack(int data)
    {
        return "Hello from static member callback! " + std::to_string(data);
    }

    std::string NonStaticRedundencyManagerCallBack(int data)
    {
        return member + std::to_string(data);
    }

    std::string withargument(std::string &mydata)
    {
        return mydata;
    }
};

std::string NonMemberCallBack(int data)
{
    return "Hello from non member function! " + std::to_string(data);
}

int main()
{
    auto instance = RedundencyManager();

    auto callback1 = std::bind(&NonMemberCallBack,1);
    std::cout << instance.Init(callback1,1) << "\n";

    // Similar to non member function.
    auto callback2 = std::bind(&CLoggersInfra::RedundencyManagerCallBack,2);
    std::cout << instance.Init(callback2, 2) << "\n";

    // Class instance is passed to std::bind as second argument.
    // (heed that I call the constructor of CLoggersInfra)
    // auto callback3 = std::bind(&CLoggersInfra::NonStaticRedundencyManagerCallBack,3, CLoggersInfra());
    // std::cout << instance.Init(callback3, 3) << "\n";

    // RedundencyManager redobj;
    // const std::string mydata = "mydata from arguments\n";

    // auto callback4 = std::bind(&CLoggersInfra::withargument, CLoggersInfra());
    // // std::cout<<redobj.Init1(callback4("abc")) << "\n";

}