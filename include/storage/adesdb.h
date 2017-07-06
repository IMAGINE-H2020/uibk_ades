#ifndef ADESDB_H
#define ADESDB_H


#include <vector>
#include "ades.h"


namespace ades {


    class AdesDB
    {
    private:
        std::vector<Ades> ades;

    public:
        AdesDB();
        
        ~AdesDB();

        bool addAdes(std::vector<Ades> ades_);
        
        bool removeAdesByName(std::string name);

        bool removeAdesByID(std::string id);

        Ades &updateAdesByName(std::string name);

        Ades &updateAdesByID(std::string id);

        std::vector<Ades>::const_iterator listAdes()
        {
            return ades.cbegin();
        }

        const Ades getAdesByName(std::string name);

        const Ades getAdesByID(std::string id);
    };    
}


#endif
