#include "Core.h"

namespace Kep
{
    class RigidBody
    {
    public:
        real inverseMass;
        
        Vector3 position;
        Quaternion orientation;
        
        Vector3 velocity;
        Vector3 rotation;
        
        Matrix4 transformMatrix;
    };
}
