#ifndef GAME_MWRENDER_PLAYER_H
#define GAME_MWRENDER_PLAYER_H

#include <string>

namespace Ogre
{
    class Vector3;
    class Camera;
    class SceneNode;
}

namespace MWWorld
{
    class Ptr;
}

namespace MWRender
{
    class NpcAnimation;
    /// \brief Player character rendering and camera control
    class Player
    {
        struct CamData {
            float pitch, yaw, offset;
        };

        Ogre::Camera *mCamera;

        Ogre::SceneNode *mPlayerNode;
        Ogre::SceneNode *mCameraNode;
        Ogre::SceneNode *mVanityNode;

        NpcAnimation *mAnimation;

        bool mFirstPersonView;
        bool mPreviewMode;

        struct {
            bool enabled, allowed, forced;
        } mVanity;

        float mHeight, mCameraDistance;
        CamData mMainCam, mPreviewCam;

        float mTimeIdle;
        int mUpdates;

        /// Updates sound manager listener data
        void updateListener();

        void rotateCamera(const Ogre::Vector3 &rot, bool adjust);

        float getYaw();
        void setYaw(float angle);

        float getPitch();
        void setPitch(float angle);

        void moveCameraNode(Ogre::SceneNode *node);

    public:

        Player (Ogre::Camera *camera, Ogre::SceneNode* mNode);

        /// Set where the player is looking at. Uses Morrowind (euler) angles
        /// \param rot Rotation angles in radians
        /// \return true if player object needs to bo rotated physically
        bool rotate(const Ogre::Vector3 &rot, bool adjust);

        std::string getHandle() const;

        /// Attach camera to object
        /// \note there is no protection from attaching the same camera to
        /// several different objects
        void attachTo(const MWWorld::Ptr &);

        void toggleViewMode();

        bool toggleVanityMode(bool enable, bool force = false);
        void allowVanityMode(bool allow);

        void togglePreviewMode(bool enable);

        void update(float duration);

        void setCameraDistance(float dist, bool adjust = false);

        void setAnimation(MWRender::NpcAnimation *anim) {
            mAnimation = anim;
        }

        void setHeight(float height);
        float getHeight();
    };
}

#endif
