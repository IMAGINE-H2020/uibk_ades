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
        uint64_t ID;
        std::vector<std::string> inputTypes_;
        std::vector<const Motion*> motions_;
        std::map<std::string, mlpack::gmm::GMM> effectModels_;


    public:
        MotionSequence(std::vector<std::string> inputTypes = std::vector<std::string>(),
                       std::vector<const Motion*> motions = std::vector<const Motion*>(),
                       std::map<std::string, mlpack::gmm::GMM> effectModels = std::map<std::string, mlpack::gmm::GMM>());

        ~MotionSequence();

        uint64_t getID() const
        {
            return ID;
        }

        void insertInputTypes(const std::vector<std::string> inputTypes);

        void removeInputTypes(const std::vector<std::string> inputTypes);

        std::vector<std::string> getInputTypes() const
        {
            return inputTypes_;
        }

        void insertMotion(const int step, const Motion *motion);

        void removeMotion(const int step);

        Motion const *modifyMotion(const int step);

        std::vector<const Motion*> getMotions() const
        {
            return motions_;
        }

        void insertEffectModel(const std::string effectType, mlpack::gmm::GMM dist);

        void removeEffectModel(const std::string effectType);

        void updateEffectModel(std::string effectType, std::vector<double> observation);

        std::map<std::string, mlpack::gmm::GMM> getEffectModels() const
        {
            return effectModels_;
        }

        double estimateParameterConfidence(const std::string effectType, std::vector<double> estimatedParameters);

        void serialize(boost::archive::xml_oarchive oa, unsigned int version);

        void deserialize(boost::archive::xml_iarchive ia, unsigned int version);

    };
}
