#include "../../include/types/motion.h"

using namespace ades;

std::map<std::string, std::vector<std::vector<double>>> DMPContainer::getMotionParameters() const
{
    std::map<std::string, std::vector<std::vector<double>>> params;
    //params.insert(std::pair<std::string, std::vector<std::vector<double>>>("", std::vector<std::vector<double>>(std::vector<std::vector<double>>(gaussianCenters))));
    return params; 
}

MotionType DMPContainer::getMotionType() const { return MotionType::DMP; }

void DMPContainer::setTemporalScale(float scaling){ temporalScale = scaling; }

bool DMPContainer::isTemporallyScalable() const { return true; }

void DMPContainer::serialize(boost::archive::xml_oarchive oa, const unsigned int version){}
void DMPContainer::deserialize(boost::archive::xml_iarchive ia, const unsigned int version){}
