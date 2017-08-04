#include "../../include/storage/adesdb.h"


using namespace std;

namespace ades {

    AdesDB::AdesDB(string home, unsigned int version) :
        home_(home),
        version_(version)
    {
        populate();
    }

    AdesDB::~AdesDB()
    {
        serialize();
    }

    bool AdesDB::populate()
    {
        //load data
        // 
        // for each ades, 
        //std::string ades_fn = "./serializedADES/fakeADES0.xml";
        //std::ifstream ifs(home_);
        //boost::archive::xml_iarchive ia(ifs);
        //ia >> BOOST_SERIALIZATION_NVP(fakeADES0);
        //ifs.close();
        return true;
    }

    bool AdesDB::serialize()
    {
        //save data
        return true;
    }

    void AdesDB::addAdes(vector<Ades> ades)
    {
        for(auto ades__ : ades)
        {
            ades_.push_back(ades__);
        }
    }

    void AdesDB::removeAdesByName(string name)
    {
        auto lambda = [name] (const Ades &a) { return a.getName() == name;};
        auto rem = remove_if(ades_.begin(), ades_.end(), lambda);
        ades_.erase(rem, ades_.end());
    }

    void AdesDB::removeAdesByID(uint64_t id)
    {
        auto lambda = [id] (const Ades &a) { return a.getID() == id;};
        auto rem = remove_if(ades_.begin(), ades_.end(), lambda);
        ades_.erase(rem, ades_.end());
    }

    std::vector<Ades>::iterator AdesDB::updateAdesByName(string name)
    {
        auto lambda = [name] (Ades &a) { return a.getName() == name;};
        auto elem = find_if(ades_.begin(), ades_.end(), lambda);
        return elem;
    }


    std::vector<Ades>::iterator AdesDB::updateAdesByID(uint64_t id) {
        auto lambda = [id] (const Ades &a) { return a.getID() == id;};
        auto elem = find_if(ades_.begin(), ades_.end(), lambda);
        return elem;
    }


    const Ades AdesDB::getAdesByName(string name)
    {
        auto lambda = [name] (Ades &a) { return a.getName() == name;};
        auto elem = find_if(ades_.begin(), ades_.end(), lambda);
        return *elem;
    }

    const Ades AdesDB::getAdesByID(uint64_t id)
    {
        auto lambda = [id] (const Ades &a) { return a.getID() == id;};
        auto elem = find_if(ades_.begin(), ades_.end(), lambda);
        return *elem;
    }
}
