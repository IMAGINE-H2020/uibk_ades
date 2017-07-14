#include "../../include/types/ades.h"
#include "../../include/types/motion_sequence.h"

using namespace std;

namespace ades {

    Ades::Ades(string name,
               map<string, string> preconditions,
               map<string, string> effects,
               map<string, MotionSequence> motions
        ) : ID(reinterpret_cast<uint64_t>(&name)),
            name_(name),
            preconditions_(preconditions),
            effects_(effects),
            motions_(motions)
    {}

    Ades::~Ades()
    {}

    void Ades::insertPreconditions(const map<string, string> conditions)
    {
        for(auto cond : conditions)
        {
            auto ret = preconditions_.insert(pair<string, string>(cond.first, cond.second));
        }
    }

    void Ades::removePreconditions(const vector<string> conditions)
    {
        if(conditions.empty())
        {
            preconditions_.clear();
        }
        else
        {
            for(auto cond : conditions)
            {
                preconditions_.erase(cond);
            }
        }
    }

    void Ades::modifyPreconditions(const map<string, string> conditions)
    {
        for(auto cond : conditions)
        {
            preconditions_.erase(cond.first);
            preconditions_.insert(pair<string, string>(cond.first, cond.second));
        }
    }

    void Ades::insertEffects(const map<string, string> effects)
    {
        for(auto effect : effects)
        {
            
            auto ret = effects_.insert(pair<string, string>(effect.first, effect.second));
        }
    }

    void Ades::removeEffects(const vector<string> effects)
    {
        if(effects.empty())
        {
            effects_.clear();
        }
        else
        {
            for(auto effect : effects)
            {
                effects_.erase(effect);
            }
        }
    }

    void Ades::modifyEffects(const map<string, string> effects)
    {
        for(auto effect : effects)
        {
            effects_.erase(effect.first);
            effects_.insert(pair<string, string>(effect.first, effect.second));
        }
    }

    void Ades::serialize(boost::archive::xml_oarchive oa, const unsigned int version)
    {

    }

    void Ades::deserialize(boost::archive::xml_iarchive ia, const unsigned int version)
    {

    }
}
