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
