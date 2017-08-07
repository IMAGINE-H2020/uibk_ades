#include "../../include/types/motion.h"

using namespace ades;

std::map<std::string, std::vector<double>> DMPContainer::getMotionParameters() const
{
    std::map<std::string, std::vector<double>> params;

    params.insert(std::pair<std::string, std::vector<double>>("gaussianCenters", gaussianCenters));
    params.insert(std::pair<std::string, std::vector<double>>("gaussianVariances", gaussianVariances));
    params.insert(std::pair<std::string, std::vector<double>>("weights", weights));
    params.insert(std::pair<std::string, std::vector<double>>("dmpCoeffs", dmpCoeffs));
    
    return params; 
}

MotionType DMPContainer::getMotionType() const { return MotionType::DMP; }

void DMPContainer::setTemporalScale(float scaling){ temporalScale = scaling; }

bool DMPContainer::isTemporallyScalable() const { return true; }

//void DMPContainer::serialize(boost::archive::xml_oarchive & oa, const unsigned int version)
/*
template <class Archive> void DMPContainer::serialize(Archive & ar, const unsigned int version)
{
    //std::cout << "Motion serialization " << count_ << std::endl;
    //count_+=1;

    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Motion);
    //std::cout << "Added Motion base class" << std::endl;

    ar & BOOST_SERIALIZATION_NVP(temporalScale);
    ar & BOOST_SERIALIZATION_NVP(name_);

    for(auto it : gaussianCenters){ ar & BOOST_SERIALIZATION_NVP(it);}
    for(auto it : gaussianVariances){ ar & BOOST_SERIALIZATION_NVP(it); }
    for(auto it : weights){ ar & BOOST_SERIALIZATION_NVP(it); }
    for(auto it : dmpCoeffs){ ar & BOOST_SERIALIZATION_NVP(it); }
}
*/

/*
void DMPContainer::serialize(boost::archive::xml_iarchive & ia, const unsigned int version)
{
    std::cout << "Motion serialization" << std::endl;

    ia & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Motion);
    std::cout << "Added Motion base class" << std::endl;

    ia & BOOST_SERIALIZATION_NVP(temporalScale);
    ia & BOOST_SERIALIZATION_NVP(name_);

    for(auto it : gaussianCenters){ ia & BOOST_SERIALIZATION_NVP(it);}
    for(auto it : gaussianVariances){ ia & BOOST_SERIALIZATION_NVP(it); }
    for(auto it : weights){ ia & BOOST_SERIALIZATION_NVP(it); }
    for(auto it : dmpCoeffs){ ia & BOOST_SERIALIZATION_NVP(it); }
}*/
