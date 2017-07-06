#ifndef MOTION_H
#define MOTION_H


#include <vector>

#include "motion_type.h"


namespace ades {

    class Motion
    {
    public:
        virtual std::vector<std::string> getMotionParameters() const = 0;

        virtual bool isTemporallyScalable() const = 0;

        virtual bool setTemporalScale(float scaling = 1.0) const = 0;

        virtual MotionType getMotionType() const = 0;

        //TODO Does predicting a duration make sense?

        //TODO Talk to KIT
    };

}


#endif
