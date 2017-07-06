#ifndef MOTION_SEQUENCE_H
#define MOTION_SEQUENCE_H


#include <vector>
#include <map>
#include <mlpack/core.hpp>
#include <mlpack/methods/gmm/gmm.hpp>


#include "motion.h"


namespace ades {

    class MotionSequence
    {
    private:
        const std::string ID;
        std::vector<std::string> inputTypes;
        std::vector<Motion> motions;
        std::map<std::string, mlpack::gmm::GMM> effectModels;
        std::map<std::string, std::vector<float*>> effectExperience;

        
    public:
        MotionSequence(const std::string ID,
                       std::vector<std::string> inputTypes = std::vector<std::string>(),
                       std::vector<Motion> motions = std::vector<Motion>(),
                       std::map<std::string, EffectDistribution> effects = std::map<std::string, EffectDistribution>());

        ~MotionSequence();


        const std::string getID()
        {
            return ID;
        }

        bool insertInputTypes(const std::vector<std::string> inputTypes);

        //if empty, remove all, otherwise what's contained
        bool removeInputTypes(const std::vector<std::string> inputTypes);

        std::vector<std::string>::const_iterator getInputTypes()
        {
            return inputTypes.cbegin();
        }

        bool insertMotion(const Motion motion);
    
        bool removeMotion(const int step);

        Motion &modifyMotion(const int step);

        std::vector<Motion>::const_iterator getMotions()
        {
            return motions.cbegin();
        }

        bool insertEffectModel(const std::string effectType, EffectDistribution dist);
    
        bool removeEffectModel(const std::string effectType);

        //add observation to experience vector and regularly (e.g., after adding 10 new observations, retrain)
        bool updateEffectModel(std::string effectType, float *observation);

        std::map<std::string, mlpack::gmm::GMM>::const_iterator getEffectModels()
        {
            return effectModels.cbegin();
        }

        std::map<std::string, std::vector<float*>>::const_iterator getEffectExperience()
        {
            return effectExperience.cbegin();
        }       
    
    };

}


#endif
