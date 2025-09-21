#include "scene.h"

namespace engine {

  Scene::Scene(const Object3D& object3D, const Camera& camera, const DirectionalLight& directionalLight) : 
    object3D{object3D}, 
    camera{camera}, 
    directionalLight{directionalLight} 
  {}
  
}
