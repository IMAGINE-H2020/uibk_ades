#pragma once


#include <vector>
#include <map>

#include "motion_type.h"
#include "../utils/serializable.h"


namespace ades {

    /*! Abstract base class to be implemented by the various motion containers.
     */
    class Motion : public Serializable
    {
    
    private:
       /*! user-defined name 
        * */    
        std::string name_;

    protected:
        float temporalScale;

    public:

        Motion(std::string name="") : name_(name){}

        ~Motion(){}
        
        std::string getName()
        {
            return name_;
        }

        void setName(std::string name)
        {
            name_ = name;
        }

        /*! Return the motion parameters associated with this motion representation.
         *  \return a vector of <string, vector> listing the motion parameters and their values
         */
        virtual std::map<std::string, std::vector<std::vector<double>>> getMotionParameters() const = 0;


        /*! Check whether this motion representation is temporally scalable.
         *  \return true if scalable, otherwise false
         */
        virtual bool isTemporallyScalable() const = 0;

        /*! Set the temporal scaling for this motion.
         *  \param scaling : a float, where 1.0 denotes no scaling
         */
        virtual void setTemporalScale(float scaling = 1.0) = 0;


        /*! Return the type of this motion (see MotionType )
         *  \return the type of this motion
         */
        virtual MotionType getMotionType() const = 0;

        //TODO Does predicting a duration make sense?
        //TODO Talk to KIT
    };

    class DMPContainer : public Motion
    {
        private:
            std::vector<double> gaussianCenters;
            std::vector<double> gaussianVariances;
            std::vector<double> weights;
            std::vector<double> dmp_coeffs;
            // dmp coeffs ordered as tau, alpha_z, beta_z, alpha_g, see dmp definition:

        public:
            DMPContainer(std::vector<double> gC = std::vector<double>(),
                         std::vector<double> gV = std::vector<double>(),
                         std::vector<double> w = std::vector<double>(),
                         std::vector<double> coeffs = std::vector<double>()
                      )
            {
                gaussianCenters = gC; 
                gaussianVariances = gV;
                weights = w;
                dmp_coeffs = coeffs;
            }

            ~DMPContainer(){}
            
            std::map<std::string, std::vector<std::vector<double>>> getMotionParameters() const;
            bool isTemporallyScalable() const;
            
            void setTemporalScale(float scaling = 1.0);

            MotionType getMotionType() const;

            void serialize(boost::archive::xml_oarchive oa, const unsigned int version);

            void deserialize(boost::archive::xml_iarchive ia, const unsigned int version);
    };

}
