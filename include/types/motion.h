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

    protected:
        float temporalScale;
        /*! user-defined name
        * */
        std::string name_;


    public:

        Motion(std::string name="", float scaling=1.0) : name_(name), temporalScale(scaling){}

        ~Motion(){}

        std::string getName() const
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
        virtual std::map<std::string, std::vector<double>> getMotionParameters() const = 0;


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

        template <class Archive> void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_NVP(temporalScale);
            ar & BOOST_SERIALIZATION_NVP(name_);
        }
        //void serialize(boost::archive::xml_oarchive & oa, const unsigned int version){ std::cout << "Virtual bananas" << std::endl; }
        //void deserialize(boost::archive::xml_iarchive & ia, const unsigned int version){}
    };
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT( ades::Motion )

namespace ades {
    class DMPContainer : public Motion
    {
        private:
            std::vector<double> gaussianCenters;
            std::vector<double> gaussianVariances;
            std::vector<double> weights;
            std::vector<double> dmpCoeffs;
            // dmp coeffs ordered as tau, alpha_z, beta_z, alpha_g, see dmp definition:
            int count_; // temp variable for testing

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
                dmpCoeffs = coeffs;
            }

            DMPContainer(const DMPContainer & d) :
                gaussianCenters(d.gaussianCenters),
                gaussianVariances(d.gaussianVariances),
                weights(d.weights),
                dmpCoeffs(d.dmpCoeffs)
           {}

            ~DMPContainer(){}

            std::map<std::string, std::vector<double>> getMotionParameters() const;
            bool isTemporallyScalable() const;

            float getTemporalScale(){ return temporalScale; }

            void setTemporalScale(float scaling = 1.0);

            MotionType getMotionType() const;

            template <class Archive> void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Motion);

                ar & BOOST_SERIALIZATION_NVP(gaussianCenters);
                ar & BOOST_SERIALIZATION_NVP(gaussianVariances);
                ar & BOOST_SERIALIZATION_NVP(weights);
                ar & BOOST_SERIALIZATION_NVP(dmpCoeffs);
             }
    };


}

//BOOST_CLASS_EXPORT( ades::DMPContainer);
//BOOST_CLASS_EXPORT_GUID(ades::DMPContainer, "DMPContainer")
