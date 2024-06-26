// 抽象工厂模式是一种创建型设计模式， 它能创建一系列相关的对象， 而无需指定其具体类。
#include <iostream>
#include <string>

/**
 * Each distinct product of a product family should have a base interface. All
 * variants of the product must implement this interface.
 */
class AbstrctProductA
{
public:
    virtual ~AbstrctProductA() {}
    virtual std::string UsefulFuntionA() const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ConcreteProductA1 : public AbstrctProductA
{
public:
    std::string UsefulFuntionA() const override
    {
        return "The result of the product A1.";
    }
};
class ConcreteProductA2 : public AbstrctProductA
{
public:
    std::string UsefulFuntionA() const override
    {
        return "The result of the product A2.";
    }
};

/**
 * Here's the the base interface of another product. All products can interact
 * with each other, but proper interaction is possible only between products of
 * the same concrete variant.
 */
class AbstrctProductB
{
    /**
     * Product B is able to do its own thing...
     */
public:
    virtual ~AbstrctProductB() {}
    virtual std::string UsefulFuntionB() const = 0;
    /**
     * ...but it also can collaborate with the ProductA.
     *
     * The Abstract Factory makes sure that all products it creates are of the
     * same variant and thus, compatible.
     */
    virtual std::string AnotherUsefulFuntionB(const AbstrctProductA &collaborator) const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ConcreteProductB1 : public AbstrctProductB
{
public:
    std::string UsefulFuntionB() const override
    {
        return "The result of the product B1.";
    }
    /**
     * The variant, Product B1, is only able to work correctly with the variant,
     * Product A1. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string AnotherUsefulFuntionB(const AbstrctProductA &collaborator) const override
    {
        const std::string result = collaborator.UsefulFuntionA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};
class ConcreteProductB2 : public AbstrctProductB
{
public:
    std::string UsefulFuntionB() const override
    {
        return "The result of the product B2.";
    }
    /**
     * The variant, Product B2, is only able to work correctly with the variant,
     * Product A2. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string AnotherUsefulFuntionB(const AbstrctProductA &collaborator) const override
    {
        const std::string result = collaborator.UsefulFuntionA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 */
class AbstractFactory
{
public:
    virtual AbstrctProductA *CreateProductA() const = 0;
    virtual AbstrctProductB *CreateProductB() const = 0;
};

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
 */
class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstrctProductA *CreateProductA() const override
    {
        return new ConcreteProductA1();
    }
    AbstrctProductB *CreateProductB() const override
    {
        return new ConcreteProductB1();
    }
};
/**
 * Each Concrete Factory has a corresponding product variant.
 */
class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstrctProductA *CreateProductA() const override
    {
        return new ConcreteProductA2();
    }
    AbstrctProductB *CreateProductB() const override
    {
        return new ConcreteProductB2();
    }
};

/**
 * The client code works with factories and products only through abstract
 * types: AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */
void ClientCode(const AbstractFactory &factory)
{
    const AbstrctProductA *produdct_a = factory.CreateProductA();
    const AbstrctProductB *produdct_b = factory.CreateProductB();
    std::cout << produdct_b->UsefulFuntionB() << std::endl;
    std::cout << produdct_b->AnotherUsefulFuntionB(*produdct_a) << std::endl;
    delete produdct_a;
    delete produdct_b;
}

int main()
{
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactory2 *f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    return 0;
}