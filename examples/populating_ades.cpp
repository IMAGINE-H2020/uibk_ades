
/* @description : This example instantiate and populate an ADES (with fake data)
 *
 * */

#include <iostream>
#include "../include/types/ades.h"
#include "../include/types/motion_sequence.h"

using namespace ades;

std::string const basic_color = "\033[97m";
std::string const info_color = "\033[92m";
std::string const error_color = "\033[31m";
std::string const default_color = "\033[39m";

std::string displayADESInfo(Ades & a)
{
    std::stringstream output;
    output << basic_color << "ADES name : " << info_color << a.getName() << std::endl;

    output << basic_color << "ADES PC : " << info_color << std::endl;
    auto ades_pc = a.getPreconditions();
    if(ades_pc.empty()){ output << error_color << "No PC defined yet"<< std::endl; }
    else
    {
        for(auto apc_it = ades_pc.begin() ; apc_it != ades_pc.end() ; apc_it++)
        {
           output << "\t" << apc_it->first << ":-" << apc_it->second << "." << std::endl;
        }
    }
    auto ades_ef = a.getEffects();
    output << basic_color << "ADES effects : " << info_color << std::endl;
    if(ades_ef.empty()){ output << error_color << "No Effects defined yet"<< std::endl; }
    else
    {
        for(auto aef_it = ades_ef.begin() ; aef_it != ades_ef.end() ; aef_it++)
        {
            output << "\t" << aef_it->first << ":-" << aef_it->second << std::endl;
        }
    }
    output << basic_color << "ADES motion sequences : " << info_color << std::endl;
    auto ades_ms = a.getMotionSequences();
    if(ades_ms.empty()){ output<< error_color <<  "Motion Sequences defined yet"<< std::endl; }
    for(auto ams_it = ades_ms.begin() ; ams_it != ades_ms.end() ; ams_it++)
    {
          output << "\t" << ams_it->first << std::endl;
          //output << ams_it->first << ":-" << (ams_it->second).getID() << std::endl;
    }
    output << default_color << "----------------------";
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
    
    fakeADES.removePreconditions();
    std::cout << displayADESInfo(fakeADES) << std::endl;
    
    // Let's insert a set of planner/categorical effects
    std::map<std::string, std::string> fakeEffects;
    fakeEffects.insert(std::pair<std::string, std::string>("levered(X)","(!gap(X))"));
    fakeADES.insertEffects(fakeEffects);
    std::cout << displayADESInfo(fakeADES) << std::endl;
    
    // Let's insert a motion sequence describing how to execute the action
    // 1st let's populate a simple motion_sequence
    MotionSequence firstMotionSequence;
    // Input dimensions to consider :
    std::string inputDimensions[] = {"target_position", "max_tool_force"};
    std::vector<std::string> fakeInputTypes(inputDimensions, inputDimensions+sizeof(inputDimensions)/sizeof(std::string));
    // List of motions :
    DMPContainer fakeDMP = DMPContainer();
    //// then add it the same way we add precondtions or effects :
    //std::map<std::string, MotionSequence> fakeMotionSequence;
    //fakeMotionSequence.insert(std::pair<std::string, MotionSequence>("firstMotion",firstMotion));
    //fakeADES.insertEffects(fakeMotionSequence);
    //MotionSequence secondMotionSequence(fakeInputTypes, );
    std::cout << displayADESInfo(fakeADES) << std::endl;
}
