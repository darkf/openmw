
#include "action.hpp"

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"

#include "../mwbase/soundmanager.hpp"

const MWWorld::Ptr& MWWorld::Action::getTarget() const
{
    return mTarget;
}

MWWorld::Action::Action (bool teleport, const Ptr& target) : mTeleport (teleport), mTarget (target)
{}

MWWorld::Action::~Action() {}

void MWWorld::Action::execute (const Ptr& actor)
{
    if (!mSoundId.empty())
    {
        if (mTeleport && actor.getRefData().getHandle()=="player")
        {
            MWBase::Environment::get().getSoundManager()->playSound(mSoundId, 1.0, 1.0,
                MWBase::SoundManager::Play_NoTrack);
        }
        else
        {
            MWBase::Environment::get().getSoundManager()->playSound3D (mTarget.isEmpty() ? actor : mTarget,
                mSoundId, 1.0, 1.0,
                mTeleport ? MWBase::SoundManager::Play_NoTrack : MWBase::SoundManager::Play_Normal);
        }
    }

    executeImp (actor);
}

void MWWorld::Action::setSound (const std::string& id)
{
    mSoundId = id;
}
