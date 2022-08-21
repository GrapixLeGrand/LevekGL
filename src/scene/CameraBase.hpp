#pragma once

namespace Levek {
class CameraBase {
public:
    virtual glm::vec3 getPosition() = 0;
    virtual float getRotation() = 0;
    virtual float getElevation() = 0;
    virtual glm::vec3 getDirection() = 0;
    virtual glm::mat4& getView() = 0;
    virtual glm::mat3& getNormalView() = 0;
    virtual glm::mat4& getViewProjection() = 0;
    virtual glm::mat4& getProjection() = 0;
    virtual glm::mat3& getViewInv() = 0;
    
    //virtual void setMaxElevation(float maxElevation);
    //virtual void setMinElevation(float minElevation);

};
}