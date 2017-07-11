#pragma once


#include <string>
#include <map>
#include <vector>
#include <iterator>


#include "motion_sequence.h"
#include "../utils/serializable.h"


namespace ades {

    class Ades : public Serializable
    {
    private:
        uint64_t ID;
        std::string name_;
        std::map<std::string, std::string> preconditions_;
        std::map<std::string, std::string> effects_;

        //TODO Explicit scene targets/affordances necessary or do preconditions suffice?

        std::map<std::string, MotionSequence> motions_;


    public:
        Ades(std::string name,
             std::map<std::string, std::string> preconditions = std::map<std::string, std::string>(),
             std::map<std::string, std::string> effects = std::map<std::string, std::string>(),
             std::map<std::string, MotionSequence> motions = std::map<std::string, MotionSequence>()
            );

        ~Ades();


        uint64_t getID() const
        {
            return ID;
        }

        std::string getName() const
        {
            return name_;
        }

        void setName(std::string name)
        {
            name_ = name;
        }

        void insertPreconditions(const std::map<std::string, std::string> conditions);

        //if empty, remove all, otherwise what's contained
        void removePreconditions(const std::vector<std::string> conditions);

        void modifyPreconditions(const std::map<std::string, std::string> conditions);

        const std::map<std::string, std::string> getPreconditions()
        {
            return preconditions_;
        }

        void insertEffects(const std::map<std::string, std::string> effects);

        void removeEffects(const std::vector<std::string> effects);

        void modifyEffects(const std::map<std::string, std::string> effects);

        const std::map<std::string, std::string>::const_iterator getEffects()
        {
            return effects_;
        }

        std::string insertMotionSequence(const std::string motionSequenceID,
                                         const MotionSequence motionSequence);

        bool removeMotionSequence(const std::string motionSequenceID);

        MotionSequence &modifyMotionSequence(const std::string motionSequenceID);

        std::map<std::string, MotionSequence>::const_iterator getMotionSequences()
        {
            return motions_.cbegin();
        }

        void serialize(boost::archive::xml_oarchive oa, unsigned int version);

        void deserialize(boost::archive::xml_iarchive ia, unsigned int version);
    };
}
