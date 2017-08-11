#pragma once


#include "../types/motion.h"

namespace ades {
    class DMPContainer : public virtual Motion
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
            {

            }

            ~DMPContainer()
            {

            }

            std::map<std::string, std::vector<double>> getMotionParameters() const {
              std::map<std::string, std::vector<double>> params;

              params.insert(std::pair<std::string, std::vector<double>>("gaussianCenters", gaussianCenters));
              params.insert(std::pair<std::string, std::vector<double>>("gaussianVariances", gaussianVariances));
              params.insert(std::pair<std::string, std::vector<double>>("weights", weights));
              params.insert(std::pair<std::string, std::vector<double>>("dmpCoeffs", dmpCoeffs));

              return params;
            }

            bool isTemporallyScalable() const
            {
              return true;
            }

            float getTemporalScale() const
            {
              return temporalScale;
            }

            void setTemporalScale(float scaling = 1.0)
            {
              temporalScale = scaling;
            }

            MotionType getMotionType() const
            {
              return MotionType::DMP;
            }

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



