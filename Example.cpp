#include <iostream>
#include "EloCpp.hpp"

int main()
{
    elo::Player David(1200,0,false);
    elo::Player Goliath(2500,50,true);

    elo::Manager::game(Goliath,David);

    std::cout << "Goliath win !" << std::endl;
    std::cout << "David : " << David.getRank() << std::endl;
    std::cout << "Goliath : " << Goliath.getRank() << std::endl;

    std::cout << std::endl;

    elo::Manager::game(David,Goliath);

    std::cout << "David win !" << std::endl;
    std::cout << "David : " << David.getRank() << std::endl;
    std::cout << "Goliath : " << Goliath.getRank() << std::endl;


    return 0;
}
