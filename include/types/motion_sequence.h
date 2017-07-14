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
        std::vector<Motion> motions_;
        std::map<std::string, mlpack::gmm::GMM> effectModels_;


    public:
        /*! Constructor for type ades::MotionSequence.
         *  \param inputTypes : vector of <string> specifying required parameters for this motion
         *                      sequence by name
         *  \param motions : vector of <Motion*> specifying a squence of motions (see Motion)
         *  \param effectModels : map of <string, mlpack::gmm::GMM> specifying probabilistic effect
         *                        models using GMMs
         */
        MotionSequence(std::vector<std::string> inputTypes = std::vector<std::string>(),
                       std::vector<const Motion*> motions = std::vector<const Motion*>(),
                       std::map<std::string, mlpack::gmm::GMM> effectModels = std::map<std::string, mlpack::gmm::GMM>());

        ~MotionSequence();

        uint64_t getID() const
        {
            return ID;
        }


        /*! Add a set of input types to this motion sequence. Checks against duplicate entries.
         *  \param inputTypes : vector of <string> specifying input types
         */
        void insertInputTypes(const std::vector<std::string> inputTypes);


        /*! Remove the specifed input types from this motion sequence.
         *  \param inputTypes : vector of <string> specifying input types to be removed
         */
        void removeInputTypes(const std::vector<std::string> inputTypes);


        /*! Return the current list of input types.
         *  \return a vector of <string> containing all input types
         */
        std::vector<std::string> getInputTypes() const
        {
            return inputTypes_;
        }

        /*! Add a motion to this motion sequence at specified step. Step hereby denotes the
         *  temporal order of execution.
         *  \param step : integer index in the motion (at which step do I do this)
         *  \param motion : the motion to insert
         */
        void insertMotion(const int step, const Motion *motion);


        /*! Remove the specifed motion (specified by its step) from this motion sequence.
         *  \param step : integer index in the motion (at which step do I do this)
         */
        void removeMotion(const int step);


        /*! Modify a motion by specifying its step. Returns a reference
         *  to a motion.
         *  \param step : integer index in the motion (at which step do I do this)
         *  \return the motion to modify
         *  \exception std::out_of_range : if the MotionSequence does not have an motion
         *                                 at the specified step
         */
        Motion const *modifyMotion(const int step);


        /*! Return the current list of motions.
         *  \return a vector of <const Motion> containing all input types
         */
        std::vector<Motion> getMotions() const
        {
            return motions_;
        }


        /*! Add an effect model to this motion sequence for the specified effect.
         *  \param effectType : an effect of <string> for which to add a model
         *  \param dist : the effect model
         */
        void insertEffectModel(const std::string effectType, mlpack::gmm::GMM dist);


        /*! Remove the specifed effect model (specified by effectType) from this motion sequence.
         *  \param effectType : an effect of <string> for which to remove a model
         */
        void removeEffectModel(const std::string effectType);


        /*! Updates the effect model for the specified effect type using a new observation.
         *  \param effectType : an effect of <string> for which to remove a model
         *  \param observation :  a vector of <double> containing a new observation
         */
        void updateEffectModel(std::string effectType, std::vector<double> observation);


        /*! Return the current list of effect models.
         *  \return a map of <string, mlpack::gmm::GMM> listing all effect types with
         *          their associated model
         */
        std::map<std::string, mlpack::gmm::GMM> getEffectModels() const
        {
            return effectModels_;
        }


        /*! Estimate the confidence of parameters in terms of specific effect, i.e.,
         *  do these parameters yield the expected effect.
         *  \param effectType : an effect of <string> for which to estimate the confidence
            \param estimatedParameters: a vector of <double> specifying the parameters for
                                        which to estimate the cofidence for a desired effect
            \return the confidence that these parameters yield the desired effect
         */
        double estimateParameterConfidence(const std::string effectType, std::vector<double> estimatedParameters);

        void serialize(boost::archive::xml_oarchive oa, unsigned int version);

        void deserialize(boost::archive::xml_iarchive ia, unsigned int version);

    };
}
