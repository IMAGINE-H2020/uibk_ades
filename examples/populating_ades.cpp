
/* @description : This example instantiate and populate an ADES (with fake data)
 *
 * */

#include <iostream>
#include "../include/types/ades.h"

using namespace ades;

std::string displayADESInfo(Ades & a)
{
    std::stringstream output;
    output << "ADES name : " << a.getName() << std::endl;

    output << "ADES PC : " << std::endl;
    for(auto apc_it = a.getPreconditions().begin() ; apc_it != a.getPreconditions().end() ; apc_it++)
    {
          output << apc_it->first << ":-" << apc_it->second << std::endl;
    }
    output << "ADES effects : " << std::endl;
    for(auto apc_it = a.getPreconditions().begin() ; apc_it != a.getPreconditions().end() ; apc_it++)
    {
          output << apc_it->first << ":-" << apc_it->second << std::endl;
    }

    return output.str();
}

int main(int argc, char **argv)
{
    Ades fakeADES = Ades("myFakeAction");
    std::cout << "Instanciated ADES :" << std::endl << "Hi, I'm \033[32m" << fakeADES.getName() << "\033[39m action descriptor \033[34m(ADES)\033[39m ;" << std::endl;
    std::cout << "Instanciated ADES :" << std::endl << "Hi, I'm \033[32m" << fakeADES.getName() << "\033[39m action descriptor \033[34m(ADES)\033[39m ;" << std::endl;
    fakeADES.setName("fakeLeverAction");
    std::cout << "setName() :" << std::endl << "Hi, now I'm \033[32m" << fakeADES.getName() << "\033[39m action descriptor \033[34m(ADES)\033[39m ;" << std::endl;
    // Let's insert a set of planner/categorical preconditions
    // here, the assumption is that preconditions are prolog-like statements, the :- is not explicit but embedded in the key-value separation
    std::map<std::string, std::string> fakePreConds;
    fakePreConds.insert(std::pair<std::string, std::string>("leverable(X)","(gap(X), reachable(X))"));
    fakeADES.insertPreconditions(fakePreConds);
    //std::cout << "insertPreconditions() :" << std::endl << "Hi, now I'm \033[32m" << fakeADES.getName() << "\033[39m action descriptor \033[34m(ADES)\033[39m ;" << std::endl;
}
