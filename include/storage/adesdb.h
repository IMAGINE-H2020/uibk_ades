#pragma once


#include <vector>
#include "../types/ades.h"


#include "../utils/serializable.h"


namespace ades {

    class AdesDB
    {
    private:
        std::string home_;

        unsigned int version_;

        std::vector<Ades> ades_;

        bool populate();

        bool serialize();

    public:
        AdesDB(std::string home, unsigned int version);

        ~AdesDB();

        std::string getHome() const
        {
            return home_;
        }

        void addAdes(std::vector<Ades> ades);

        void removeAdesByName(std::string name);

        void removeAdesByID(uint64_t id);

        std::vector<Ades>::iterator updateAdesByName(std::string name);

        std::vector<Ades>::iterator updateAdesByID(uint64_t id);

        std::vector<Ades>::const_iterator listAdes()
        {
            return ades_.cbegin();
        }

        const Ades getAdesByName(std::string name);

        const Ades getAdesByID(uint64_t id);
    };
}
