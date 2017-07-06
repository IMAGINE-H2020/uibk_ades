#ifndef ADES_H
#define ADES_H


#include <string>
#include <map>
#include <vector>
#include <iterator>

#include "motion_sequence.h"

namespace ades {

    class Ades
    {
    private:
        //symbolic
        const std::string ID;
        std::string name;
        std::map<std::string, std::string> preconditions;
        std::map<std::string, std::string> effects;

        //TODO Explicit scene targets/affordances necessary or do preconditions suffice?
    
        //subsymbolic
        std::map<std::string, MotionSequence> motions;
    
    
    public:
        Ades(std::string name,
             std::map<std::string, std::string> preconditions = std::map<std::string, std::string>(),
             std::map<std::string, std::string> effects = std::map<std::string, std::string>(),
             std::map<std::string, MotionSequence> motions = std::map<std::string, MotionSequence>()
            );
    
        ~Ades();

    
        const std::string getID()
        {
            return ID;
        }

        std::string getName()
        {
            return name;
        }

        void setName(std::string name)
        {
            this->name = name;
        }

        bool insertPreconditions(const std::map<std::string, std::string> conditions);

        //if empty, remove all, otherwise what's contained
        bool removePreconditions(const std::vector<std::string> conditions);

        bool modifyPreconditions(const std::map<std::string, std::string> conditions);

        std::map<std::string, std::string>::const_iterator getPreconditions()
        {
            return preconditions.cbegin();
        }

        bool insertEffects(const std::map<std::string, std::string> effects);
    
        bool removeEffects(const std::vector<std::string> effects);

        bool modifyEffects(const std::map<std::string, std::string> effects);

        std::map<std::string, std::string>::const_iterator getEffects()
        {
            return effects.cbegin();
        }

        std::string insertMotionSequence(const std::string motionSequenceID,
                                         const MotionSequence motionSequence);
    
        bool removeMotionSequence(const std::string motionSequenceID);

        MotionSequence &modifyMotionSequence(const std::string motionSequenceID);

        std::map<std::string, MotionSequence>::const_iterator getMotionSequences()
        {
            return motions.cbegin();
        }    
    };
}

#endif
