#pragma once


#include <vector>
#include "ades.h"


namespace ades {


    class AdesDB
    {
    private:
        std::string home;

        std::vector<Ades> ades;

        bool populate();

        bool serialize();

    public:
        AdesDB(std::string home_);

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
