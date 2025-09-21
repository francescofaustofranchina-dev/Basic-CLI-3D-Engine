#ifndef SCENE_H
#define SCENE_H

#include "entity/camera/camera.h"
#include "entity/light/directional_light.h"
#include "entity/object3d/object3d.h"

namespace engine {

  class Scene {
  public:
    Scene(const Object3D& object3D, const Camera& camera, const DirectionalLight& directionalLight);

    Object3D object3D;
    Camera camera;
    DirectionalLight directionalLight;
  };
  
}

#endif
