// 适配器模式是一种结构型设计模式， 它能使接口不兼容的对象能够相互合作。
#include <iostream>
#include <string>
#include <algorithm>

/**
 * The Target defines the domain-specific interface used by the client code.
 */
class Target
{
public:
    virtual ~Target() = default;

    virtual std::string Request() const
    {
        return "Target: The default target's behavior.";
    }
};

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class Adaptee
{
public:
    std::string SpecificRequest() const
    {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface.
 */
class Adapter1 : public Target
{
private:
    Adaptee *adaptee_;

public:
    Adapter1(Adaptee *adaptee) : adaptee_(adaptee) {}
    std::string Request() const override
    {
        std::string to_reverse = adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter1: (TRANSLATED) " + to_reverse;
    }
};

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface using multiple inheritance.
 */
class Adapter2 : public Target, public Adaptee
{
public:
    Adapter2() {}
    std::string Request() const override
    {
        std::string to_reverse = SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter2: (TRANSLATED) " + to_reverse;
    }
};

/**
 * The client code supports all classes that follow the Target interface.
 */
void ClientCode(const Target *target)
{
    std::cout << target->Request();
}

int main()
{
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    std::cout << "\n\n";
    Adaptee *adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter1 *adapter1 = new Adapter1(adaptee);
    ClientCode(adapter1);
    std::cout << std::endl;
    Adapter2 *adapter2 = new Adapter2;
    ClientCode(adapter2);
    std::cout << std::endl;

    delete target;
    delete adaptee;
    delete adapter1;
    delete adapter2;

    return 0;
}
