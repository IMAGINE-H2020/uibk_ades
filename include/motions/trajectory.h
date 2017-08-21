#pragma once

#include "../types/motion.h"

namespace ades {
    class TrajectoryContainer : public virtual Motion
    {
        private:
            std::vector<std::pair<double, double>> points;

        public:
            TrajectoryContainer(std::vector<std::pair<double, double>> p = std::vector<std::pair<double, double>>()) :
                points(p)
            {
            }

            TrajectoryContainer(const TrajectoryContainer & d) :
                points(d.points)
            {

            }

            ~TrajectoryContainer()
            {
            }

            std::map<std::string, std::vector<double>> getMotionParameters() const
            {
                std::map<std::string, std::vector<double>> params;
                
                std::vector<double> x;
                std::vector<double> y;
                for(auto p : points)
                {
                    x.push_back(p.first);
                    y.push_back(p.second);
                }
                params.insert(std::pair<std::string, std::vector<double>>("points_x", x));
                params.insert(std::pair<std::string, std::vector<double>>("points_y", y));
                
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
              return MotionType::Trajectory;
            }

            template <class Archive> void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Motion);

                ar & BOOST_SERIALIZATION_NVP(points);
             }
    };

}
