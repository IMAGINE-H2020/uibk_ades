#pragma once


#include <vector>
#include <map>
#include <mlpack/core.hpp>
#include <mlpack/methods/gmm/gmm.hpp>
#include <armadillo>


#include "motion.h"
#include "../utils/serializable.h"


namespace ades {

    class MotionSequence : public Serializable
    {
    private:
        const uint64_t ID;
        std::vector<std::string> inputTypes_;
        std::vector<const Motion*> motions_;
        std::map<std::string, mlpack::gmm::GMM> effectModels_;


    public:
        MotionSequence(std::vector<std::string> inputTypes = std::vector<std::string>(),
                       std::vector<const Motion*> motions = std::vector<const Motion*>(),
                       std::map<std::string, mlpack::gmm::GMM> effectModels = std::map<std::string, mlpack::gmm::GMM>());

        ~MotionSequence();

        const uint64_t getID()
        {
            return ID;
        }

        void insertInputTypes(const std::vector<std::string> inputTypes);

        void removeInputTypes(const std::vector<std::string> inputTypes);

        std::vector<std::string>::const_iterator getInputTypes()
        {
            return inputTypes_.cbegin();
        }

        void insertMotion(const int step, const Motion *motion);

        void removeMotion(const int step);

        Motion const *modifyMotion(const int step);

        std::vector<const Motion*>::const_iterator getMotions()
        {
            return motions_.cbegin();
        }

        void insertEffectModel(const std::string effectType, mlpack::gmm::GMM dist);

        void removeEffectModel(const std::string effectType);

        void updateEffectModel(std::string effectType, std::vector<double> observation);

        std::map<std::string, mlpack::gmm::GMM>::const_iterator getEffectModels()
        {
            return effectModels_.cbegin();
        }

        double estimateParameterConfidence(const std::string effectType, std::vector<double> estimatedParameters);

        void serialize(boost::archive::xml_oarchive oa, unsigned int version);

        void deserialize(boost::archive::xml_iarchive ia, unsigned int version);

    };
}
