
/* @description : This example instantiate and populate an ADES (with fake data)
 *
 * */

#include <iostream>
#include "../include/types/ades.h"

using namespace ades;

std::string displayADESInfo(Ades & a)
{
    std::stringstream output;
    output << "ADES name : \033[32m" << a.getName() << "\033[39m" << std::endl;

    output << "ADES PC : \033[33m" << std::endl;
    const std::map<std::string, std::string> ades_pc = a.getPreconditions();
    if(ades_pc.empty()){ output<< "No PC defined yet"<< std::endl; }
    else
    {
        for(auto apc_it = ades_pc.begin() ; apc_it != ades_pc.end() ; apc_it++)
        {
           output << apc_it->first << ":-" << apc_it->second << std::endl;
        }
    }
    const std::map<std::string, std::string> ades_ef = a.getEffects();
    output << "\033[39mADES effects : \033[33m" << std::endl;
    if(ades_ef.empty()){ output<< "No Effects defined yet"<< std::endl; }
    else
    {
        for(auto aef_it = ades_pc.begin() ; aef_it != ades_pc.end() ; aef_it++)
        {
            output << aef_it->first << ":-" << aef_it->second << std::endl;
        }
    }
    output << "\033[39mADES motion sequences : \033[33m" << std::endl;
   // for(auto ams_it = a.getMotionSequences().begin() ; ams_it != a.getMotionSequences().end() ; ams_it++)
   // {
   //       output << ams_it->first << std::endl;
   //       //output << ams_it->first << ":-" << (ams_it->second).getID() << std::endl;
   // }

    return output.str();
}

int main(int argc, char **argv)
{
    Ades fakeADES = Ades("myFakeAction");
    std::cout << displayADESInfo(fakeADES) << std::endl;
    fakeADES.setName("fakeLeverAction");
    std::cout << displayADESInfo(fakeADES) << std::endl;
    // Let's insert a set of planner/categorical preconditions
    // here, the assumption is that preconditions are prolog-like statements, the :- is not explicit but embedded in the key-value separation
    std::map<std::string, std::string> fakePreConds;
    fakePreConds.insert(std::pair<std::string, std::string>("leverable(X)","(gap(X), reachable(X))"));
    fakeADES.insertPreconditions(fakePreConds);
    std::cout << displayADESInfo(fakeADES) << std::endl;
}
