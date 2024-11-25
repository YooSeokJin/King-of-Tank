#include "ModelMatrix.h"

#include "glm/gtc/matrix_transform.hpp"
ModelMatrix::ModelMatrix()
	: myLocation(0.0f, 0.0f, 0.0f), myScale(1.0f, 1.0f, 1.0f), myRotation(0.0f, 0.0f, 0.0f)
{
    parent = nullptr;
    pivot = nullptr;
}
ModelMatrix::ModelMatrix(const glm::vec3& center, const glm::vec3& scale, float rZ)
    :myLocation(center), myScale(scale), myRotation(0.0f, 0.0f, rZ)
{
    parent = nullptr;
    pivot = nullptr;
}
ModelMatrix::~ModelMatrix()
{
    printf("ModelMatrix Delete\n");
    parent = nullptr;
    delete pivot;
}
// Translate
glm::vec3 ModelMatrix::getLocation() const { return myLocation; }
float ModelMatrix::getLocationX() const { return myLocation.x; }
float ModelMatrix::getLocationY() const { return myLocation.y; }
float ModelMatrix::getLocationZ() const { return myLocation.z; }

void ModelMatrix::setLocation(const glm::vec3& newLocation) { myLocation = newLocation; }
void ModelMatrix::setLocationX(float newX) { myLocation.x = newX; }
void ModelMatrix::setLocationY(float newY) { myLocation.y = newY; }
void ModelMatrix::setLocationZ(float newZ) { myLocation.z = newZ; }

void ModelMatrix::translate(const glm::vec3& deltaPosition) { myLocation += deltaPosition; }
void ModelMatrix::translateX(float deltaX) { myLocation.x += deltaX; }
void ModelMatrix::translateY(float deltaY){ myLocation.y += deltaY; }
void ModelMatrix::translateZ(float deltaZ) { myLocation.z += deltaZ; }

// Rotation
glm::vec3 ModelMatrix::getRotation() const { return myRotation; }
float ModelMatrix::getRotationX() const { return myRotation.x; }
float ModelMatrix::getRotationY() const { return myRotation.y; }
float ModelMatrix::getRotationZ() const { return myRotation.z; }

void ModelMatrix::setRotation(const glm::vec3& newAngle) {
    myRotation = newAngle;

    // 각 축의 회전 각도를 0 ~ 360 사이로 제한
    myRotation.x = fmod(myRotation.x, 360.0f);
    if (myRotation.x < 0.0f) {
        myRotation.x += 360.0f;
    }

    myRotation.y = fmod(myRotation.y, 360.0f);
    if (myRotation.y < 0.0f) {
        myRotation.y += 360.0f;
    }

    myRotation.z = fmod(myRotation.z, 360.0f);
    if (myRotation.z < 0.0f) {
        myRotation.z += 360.0f;
    }
}
void ModelMatrix::setRotationZ(float newAngleZ) {
    myRotation.z = fmod(newAngleZ, 360.0f);
    if (myRotation.z < 0.0f) {
        myRotation.z += 360.0f;
    }
}

void ModelMatrix::setRotationX(float newAngleX) {
    myRotation.x = fmod(newAngleX, 360.0f);
    if (myRotation.x < 0.0f) {
        myRotation.x += 360.0f;
    }
}

void ModelMatrix::setRotationY(float newAngleY) {
    myRotation.y = fmod(newAngleY, 360.0f);
    if (myRotation.y < 0.0f) {
        myRotation.y += 360.0f;
    }
}


void ModelMatrix::rotate(const glm::vec3& deltaAngle) {
    myRotation += deltaAngle;

    // 각도 제한 (360도로 정규화)
    myRotation.x = fmod(myRotation.x, 360.0f);
    if (myRotation.x < 0.0f) myRotation.x += 360.0f;

    myRotation.y = fmod(myRotation.y, 360.0f);
    if (myRotation.y < 0.0f) myRotation.y += 360.0f;

    myRotation.z = fmod(myRotation.z, 360.0f);
    if (myRotation.z < 0.0f) myRotation.z += 360.0f;
}

void ModelMatrix::rotateZ(float deltaAngleZ) {
    myRotation.z += deltaAngleZ;

    // z축 각도 제한 (360도로 정규화)
    myRotation.z = fmod(myRotation.z, 360.0f);
    if (myRotation.z < 0.0f) myRotation.z += 360.0f;
}

void ModelMatrix::rotateX(float deltaAngleX) {
    myRotation.x += deltaAngleX;

    // x축 각도 제한 (360도로 정규화)
    myRotation.x = fmod(myRotation.x, 360.0f);
    if (myRotation.x < 0.0f) myRotation.x += 360.0f;
}

void ModelMatrix::rotateY(float deltaAngleY) {
    myRotation.y += deltaAngleY;

    // y축 각도 제한 (360도로 정규화)
    myRotation.y = fmod(myRotation.y, 360.0f);
    if (myRotation.y < 0.0f) myRotation.y += 360.0f;
}

// Scale
glm::vec3 ModelMatrix::getScale() const { return myScale; }
float ModelMatrix::getScaleX() const { return myScale.x; }
float ModelMatrix::getScaleY() const { return myScale.y; }
float ModelMatrix::getScaleZ() const{return myScale.z;}

void ModelMatrix::setScale(const glm::vec3& newScale) { myScale = newScale; }
void ModelMatrix::setScaleX(float newX) {	myScale.x = newX; }
void ModelMatrix::setScaleY(float newY) {	myScale.y = newY;}
void ModelMatrix::setScaleZ(float newZ) { myScale.z = newZ;}

void ModelMatrix::scale(const glm::vec3& deltaScale){ myScale += deltaScale;}
void ModelMatrix::scaleX(float deltaX){ myScale.x += deltaX;}
void ModelMatrix::scaleY(float deltaY){ myScale.y += deltaY;}
void ModelMatrix::scaleZ(float deltaZ){ myScale.z += deltaZ;}

void ModelMatrix::resetAll()
{
    myRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    myLocation = glm::vec3(0.0f, 0.f, 0.f);
    myScale = glm::vec3(1.f, 1.f, 1.f);
}

void ModelMatrix::reset_Lo_Ra()
{
    myRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    myLocation = glm::vec3(0.0f, 0.f, 0.f);
}

void ModelMatrix::setPivot(float x, float y, float z)
{
    if (pivot) {
        delete pivot;
        pivot = nullptr;
    }
    pivot = new glm::vec3(x, y, z);
}

void ModelMatrix::setPivot(const glm::vec3& pivot_)
{
    if (pivot) {
        delete pivot;
        pivot = nullptr;
    }
    pivot = new glm::vec3(pivot_);
}

glm::mat4 ModelMatrix::getTransformMatrix()
{
    glm::mat4 transform = glm::mat4(1.0f);
    if (parent) {
        transform = parent->getTransformMatrix();
    }
    transform = glm::translate(transform, myLocation);

    if (pivot) {
        glm::vec3 to = *pivot - myLocation;
        transform = glm::translate(transform, *pivot);

        transform = glm::rotate(transform, glm::radians(myRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(myRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(myRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        transform = glm::translate(transform, -*pivot);
    }

    else {
        transform = glm::rotate(transform, glm::radians(myRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(myRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(myRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    transform = glm::scale(transform, myScale);
   
    return transform;
}

void ModelMatrix::setParent(ModelMatrix* p)
{
    parent = p;
}

void ModelMatrix::deleteParent()
{
    parent = nullptr;
}
