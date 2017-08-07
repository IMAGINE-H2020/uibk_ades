#pragma once

#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

class Serializable
{
    private:
        friend class boost::serialization::access;

        template <class Archive> void serialize(Archive & ar, const unsigned int version){}
        //virtual void serialize(boost::archive::xml_oarchive & oa, const unsigned int version) = 0;
        //virtual void serialize(boost::archive::xml_iarchive & ia, const unsigned int version) = 0;
        //virtual void deserialize(boost::archive::xml_iarchive & ia, const unsigned int version) = 0;
};
