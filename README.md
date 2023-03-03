# Abstract Factory and Singleton Patterns in C++
This is a C++ program that demonstrates the use of the Abstract Factory and Singleton design patterns. The program offers the user the choice between two coffee shops, one Italian-style and one American-style, and then creates objects using the chosen coffee shop (i.e., an instance of the Abstract Factory pattern).

The program defines two concrete coffee classes: Espresso and Latte, representing the drinks with the same names. It also defines two concrete coffee shops: the Italian coffee shop and the American coffee shop, which create the respective objects.

The program uses a class template to create coffee objects of any kind. A CoffeeShopSingleton class, which follows the Singleton pattern, uses the Abstract Factory design pattern to create coffee objects and stores an instance of a CoffeeShop object when requested.

A CoffeeIDRecorder class records and displays the IDs of the created coffees. IDs are generated using C++'s mt19937 RNG.

# Usage
To compile and run the program, you can use the following commands:


```
g++ -o coffee coffee.cpp
./coffee
```
The program will prompt the user to choose a coffee shop, create two coffee objects using the selected coffee shop, record their IDs, and display them.
