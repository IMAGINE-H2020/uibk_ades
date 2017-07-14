#pragma once


#include <vector>

#include "motion_type.h"
#include "../utils/serializable.h"


namespace ades {

    /*! Abstract base class to be implemented by the various motion containers.
     */
    class Motion : public Serializable
    {
    public:
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
        virtual void setTemporalScale(float scaling = 1.0) const = 0;


        /*! Return the type of this motion (see MotionType)
         *  \return the type of this motion
         */
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
