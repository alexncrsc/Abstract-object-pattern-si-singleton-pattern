#include <iostream>
#include <random>
#include <vector>


// Tema programului este de a imbina abstract object pattern si singleton pattern
// Programul ii ofera utilizatorului optiunea sa aleaga dintre doua cafenele, una in stil italinesc si una in stil american
// Apoi se creaza obiecte folosindu-se cafeneaua respectiva (cf. abstract object pattern)
// Pentru cerinta "metoda clone", am folosit o clasa care memoreaza id-urile si dupa ce cafeaua se "serveste" (metoda virtuala de afisare), id-urile inregistrate se afiseaza
// Se folosesc class templates de asemenea, se pot crea obiecte de tip coffee de orice fel
// Se definesc doua coffe classes: Espresso si Latte care reprezinta bauturile cu aceleasi nume
// De asemenea, se definesc doua coffe shops: cel in stil italian si cel in stil american care creaza obiectele respective
// Clasa CoffeeShopSingleton de tip singleton pattern se foloseste de abstract factory design pattern sa creeze obiecte de tip coffee si memoreaza o instanta a unui obiect de tio CoffeeShop cand ii este requested
// CoffeeIDRecorder este o clasa care memoreaza si afiseaza id-urile cafelelor
// Id-urile sunt generate cu un rng din C++, mt19937



// Abstract product interface
template <typename T>
class Coffee
{
public:
    virtual ~Coffee() {}
    virtual void serve() = 0;
    virtual int getID() = 0;
};

// Concrete product 1
template <typename T>
class Espresso : public Coffee<T>
{
private:
    static std::mt19937 rng;
    static std::uniform_int_distribution<int> dist;
    int id;

public:
    Espresso()
    {
        id = dist(rng);
    }

    void serve()
    {
        std::cout << "Se serveste Espresso-ul cu id-ul " << id << "." << std::endl;
    }

    int getID()
    {
        return id;
    }
};

template <typename T>
std::mt19937 Espresso<T>::rng(std::random_device{}());

template <typename T>
std::uniform_int_distribution<int> Espresso<T>::dist(1, 1000);

// Concrete product 2
template <typename T>
class Latte : public Coffee<T>
{
private:
    static std::mt19937 rng;
    static std::uniform_int_distribution<int> dist;
    int id;

public:
    Latte()
    {
        id = dist(rng);
    }

    void serve()
    {
        std::cout << "Se serveste Latte-ul cu id-ul " << id << "." << std::endl;
    }

    int getID()
    {
        return id;
    }
};

template <typename T>
std::mt19937 Latte<T>::rng(std::random_device{}());

template <typename T>
std::uniform_int_distribution<int> Latte<T>::dist(1, 1000);

// Abstract factory interface
template <typename T>
class CoffeeShop
{
public:
    virtual ~CoffeeShop() {}
    virtual Coffee<T>* createCoffee() = 0;
};

// Concrete factory 1
template <typename T>
class ItalianCoffeeShop : public CoffeeShop<T>
{
public:
    Coffee<T>* createCoffee()
    {
        return new Espresso<T>();
    }
};

// Concrete factory 2
template <typename T>
class AmericanCoffeeShop : public CoffeeShop<T>
{
public:
    Coffee<T>* createCoffee()
    {
        return new Latte<T>();
    }
};


// Singleton factory class
template <typename T>
class CoffeeShopSingleton
{
private:
    static CoffeeShopSingleton<T>* instance;
    CoffeeShop<T>* coffeeShop;

    CoffeeShopSingleton(CoffeeShop<T>* s) : coffeeShop(s) {}

public:
    static CoffeeShopSingleton<T>* getInstance(CoffeeShop<T>* s)
    {
        if (!instance)
            instance = new CoffeeShopSingleton(s);
        return instance;
    }

    Coffee<T>* createCoffee()
    {
        return coffeeShop->createCoffee();
    }
};

template <typename T>
class CoffeeIDRecorder
{
private:
    std::vector<int> ids;

public:
    void recordID(Coffee<T>* coffee)
    {
        ids.push_back(coffee->getID());
    }

    void printIDs()
    {
        std::cout << "ID-urile cafelelor: ";
        for (int id : ids)
            std::cout << id << " ";
        std::cout << std::endl;
    }
};

template <typename T>
CoffeeShopSingleton<T>* CoffeeShopSingleton<T>::instance = 0;

//

int main()
{
    std::cout << "Introduceeti 1 pentru cafeneaua in stil italian ori 2 pentru cafeneaua in stil american: ";
    int input;
    std::cin >> input;

    CoffeeShop<int>* coffeeShop;
    if (input == 1)
        coffeeShop = new ItalianCoffeeShop<int>();
    else
        coffeeShop = new AmericanCoffeeShop<int>();

    CoffeeShopSingleton<int>* singleton = CoffeeShopSingleton<int>::getInstance(coffeeShop);

    CoffeeIDRecorder<int> recorder;

    Coffee<int>* coffee = singleton->createCoffee();
    recorder.recordID(coffee);
    coffee->serve();

    delete coffee;

    coffee = singleton->createCoffee();
    recorder.recordID(coffee);
    coffee->serve();

    delete coffee;

    recorder.printIDs();

    delete singleton;

    return 0;
}