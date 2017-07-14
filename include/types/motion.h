#pragma once


#include <vector>

#include "motion_type.h"
#include "../utils/serializable.h"


namespace ades {

    class Motion : public Serializable
    {
    public:
        virtual std::vector<std::string> getMotionParameters() const = 0;

        virtual bool isTemporallyScalable() const = 0;

        virtual bool setTemporalScale(float scaling = 1.0) const = 0;

        virtual MotionType getMotionType() const = 0;

        //TODO Does predicting a duration make sense?
        //TODO Talk to KIT
    };

    class DMPContainer : public Motion
    {
        private:
        public :
            DMPContainer();
            ~DMPContainer();
            MotionType getMotionType(){ return MotionType::DMP; }
    };

}
