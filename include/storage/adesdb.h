#pragma once


#include <vector>
#include "../types/ades.h"


#include "../utils/serializable.h"


namespace ades {

    class AdesDB : public Serializable
    {
    private:
        std::string home_;

        std::vector<Ades> ades_;

        bool populate();

        bool serialize();

    public:
        AdesDB(std::string home);

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

        void serialize(boost::archive::xml_oarchive oa, unsigned int version);

        void deserialize(boost::archive::xml_iarchive ia, unsigned int version);

    };
}
