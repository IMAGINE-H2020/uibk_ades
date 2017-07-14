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
        /* Constructor for type ades::Ades.
        *\param preconditions : map of <string, string> storing symbolic precondition descriptions in a Prolog-like style; e.g., <head, body>
        *\param effects : map of <string, string> storing symbolic effect descriptions in a Prolog-like style; e.g., <head, body>
        *\param motions : map of <string, MotionSequence> storing subsymbolic motion sequences (see Motion and MotionSequence for more information)
        */
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

        /* Add a set of new preconditions to this Ades. Existing preconditions will be ignored.
         *\param conditions : map of <string, string> storing symbolic precondition descriptions in a Prolog-like style; e.g., <head, body>
         */
        void insertPreconditions(const std::map<std::string, std::string> conditions);

        /* Remove the preconditions whose head appears in conditions. If conditions is empty, remove all preconditions.
         */
        void removePreconditions(const std::vector<std::string> conditions = std::vector<std::string>());

        void modifyPreconditions(const std::map<std::string, std::string> conditions);

        std::map<std::string, std::string> getPreconditions() const
        {
            return preconditions_;
        }

        /* Add a set of effects to this Ades. Existing effects will be ignored.
        *\param effects : map of <string, string> storing symbolic effect descriptions in a Prolog-like style; e.g., <head, body>
          */
        void insertEffects(const std::map<std::string, std::string> effects);

        /* Remove the effects whose head appears in conditions. If effects is empty, remove all effects.
         * */
        void removeEffects(const std::vector<std::string> effects = std::vector<std::string>());

        void modifyEffects(const std::map<std::string, std::string> effects);

        std::map<std::string, std::string> getEffects() const
        {
            return effects_;
        }

        /*
         * *\param motions : map of <string, MotionSequence> storing subsymbolic motion sequences (see Motion and MotionSequence for more information)
         * */
        std::string insertMotionSequence(const std::string motionSequenceID,
                                         const MotionSequence motionSequence);

        bool removeMotionSequence(const std::string motionSequenceID);

        MotionSequence &modifyMotionSequence(const std::string motionSequenceID);

        std::map<std::string, MotionSequence> getMotionSequences() const
        {
            return motions_;
        }

        void serialize(boost::archive::xml_oarchive oa, unsigned int version);

        void deserialize(boost::archive::xml_iarchive ia, unsigned int version);
    };
}
