#include "../../include/types/motion_sequence.h"

using namespace std;

namespace ades {

    MotionSequence::MotionSequence(vector<string> inputTypes,
                                   vector<const Motion*> motions,
                                   map<string, mlpack::gmm::GMM> effectModels
        ) : ID(reinterpret_cast<uint64_t>(&inputTypes)),
            inputTypes_(inputTypes),
            motions_(motions),
            effectModels_(effectModels)
    {}

    void MotionSequence::insertInputTypes(const vector<string> inputTypes)
    {
        for(auto inputType : inputTypes) {
            inputTypes_.push_back(inputType);
        }
    }

    void MotionSequence::removeInputTypes(const vector<string> inputTypes)
    {
        for(auto inputType : inputTypes_) {
            auto it = find(inputTypes_.begin(), inputTypes_.end(), inputType);
            if(it != inputTypes_.end()) {
                inputTypes_.erase(it);
            }
        }
    }

    void MotionSequence::insertMotion(const int step, const Motion *motion)
    {
        motions_.insert(motions_.begin()+step, motion);
    }

    void MotionSequence::removeMotion(const int step)
    {
        motions_.erase(motions_.begin() + step);
    }

    Motion const *MotionSequence::modifyMotion(const int step)
    {
        return motions_.at(step);
    }

    void MotionSequence::insertEffectModel(const string effectType, mlpack::gmm::GMM dist)
    {
        effectModels_.insert(pair<string, mlpack::gmm::GMM>(effectType, dist));
    }

    void MotionSequence::removeEffectModel(const string effectType)
    {
        effectModels_.erase(effectType);
    }

    void MotionSequence::updateEffectModel(string effectType, vector<double> observation)
    {
        arma::mat observation_(observation);
        effectModels_.at(effectType).Train(observation_, 1, true);
    }

    double MotionSequence::estimateParameterConfidence(const std::string effectType, std::vector<double> estimatedParameters)
    {
        arma::vec estimatedParameters_(estimatedParameters);
        return effectModels_.at(effectType).Probability(estimatedParameters_);
    }

    void MotionSequence::serialize(boost::archive::xml_oarchive oa, const unsigned int version)
    {

    }

    void MotionSequence::deserialize(boost::archive::xml_iarchive ia, const unsigned int version)
    {
        //mlpack allows serializing/deserializing models
    }
}
