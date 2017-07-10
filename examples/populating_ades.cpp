
/* @description : This example instantiate and populate an ADES (with fake data)
 *
 * */

#include <iostream>
#include "../include/types/ades.h"

using namespace ades;

int main(int argc, char **argv)
{
    Ades fakeADES = Ades("myFakeAction");
    std::cout << "Hi, I'm \033[32m" << fakeADES.getName() << "\033[39m action descriptor \033[34m(ADES)\033[39m ; please interact with me !" << std::endl;
}
