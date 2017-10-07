/*! \file motion_type.h */

#pragma once
#include <string>

namespace ades {

    const int motionTypeNb = 5;
     /*! Defining the types of movement representations currently support by libades. */
    enum class MotionType { DMP, Trajectory, Cyclic, VisualServoing, PID };

    //std::string typeToString(int mt);
    std::string typeToString(enum MotionType mt);
    // Future implementation enum typeToString(enum MotionType mt);

}
