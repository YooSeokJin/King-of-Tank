#include "ModelMatrix.h"

#include "glm/gtc/matrix_transform.hpp"
ModelMatrix::ModelMatrix()
	: location_(0.0f, 0.0f, 0.0f), scale_(1.0f, 1.0f, 1.0f), rotation_(0.0f, 0.0f, 0.0f)
{
    parent_ = nullptr;
    pivotPoint_ = nullptr;
}
ModelMatrix::ModelMatrix(const glm::vec3& center, const glm::vec3& scale, float rZ)
    :location_(center), scale_(scale), rotation_(0.0f, 0.0f, rZ)
{
    parent_ = nullptr;
    pivotPoint_ = nullptr;
}
ModelMatrix::~ModelMatrix()
{
    printf("ModelMatrix Delete\n");
    parent_ = nullptr;
    delete pivotPoint_;
}
// Translate
glm::vec3 ModelMatrix::getLocation() const { return location_; }
float ModelMatrix::getLocationX() const { return location_.x; }
float ModelMatrix::getLocationY() const { return location_.y; }
float ModelMatrix::getLocationZ() const { return location_.z; }

void ModelMatrix::setLocation(const glm::vec3& newLocation) { location_ = newLocation; }
void ModelMatrix::setLocationX(float newX) { location_.x = newX; }
void ModelMatrix::setLocationY(float newY) { location_.y = newY; }
void ModelMatrix::setLocationZ(float newZ) { location_.z = newZ; }

void ModelMatrix::moveLocation(const glm::vec3& deltaPosition) { location_ += deltaPosition; }
void ModelMatrix::moveLocationX(float deltaX) { location_.x += deltaX; }
void ModelMatrix::moveLocationY(float deltaY){ location_.y += deltaY; }
void ModelMatrix::moveLocationZ(float deltaZ) { location_.z += deltaZ; }

// Rotation
glm::vec3 ModelMatrix::getRotation() const { return rotation_; }
float ModelMatrix::getRotationX() const { return rotation_.x; }
float ModelMatrix::getRotationY() const { return rotation_.y; }
float ModelMatrix::getRotationZ() const { return rotation_.z; }

void ModelMatrix::setRotation(const glm::vec3& newAngle) {
    rotation_ = newAngle;

    // 각 축의 회전 각도를 0 ~ 360 사이로 제한
    rotation_.x = fmod(rotation_.x, 360.0f);
    if (rotation_.x < 0.0f) {
        rotation_.x += 360.0f;
    }

    rotation_.y = fmod(rotation_.y, 360.0f);
    if (rotation_.y < 0.0f) {
        rotation_.y += 360.0f;
    }

    rotation_.z = fmod(rotation_.z, 360.0f);
    if (rotation_.z < 0.0f) {
        rotation_.z += 360.0f;
    }
}
void ModelMatrix::setRotationZ(float newAngleZ) {
    rotation_.z = fmod(newAngleZ, 360.0f);
    if (rotation_.z < 0.0f) {
        rotation_.z += 360.0f;
    }
}

void ModelMatrix::setRotationX(float newAngleX) {
    rotation_.x = fmod(newAngleX, 360.0f);
    if (rotation_.x < 0.0f) {
        rotation_.x += 360.0f;
    }
}

void ModelMatrix::setRotationY(float newAngleY) {
    rotation_.y = fmod(newAngleY, 360.0f);
    if (rotation_.y < 0.0f) {
        rotation_.y += 360.0f;
    }
}


void ModelMatrix::rotate(const glm::vec3& deltaAngle) {
    rotation_ += deltaAngle;

    // 각도 제한 (360도로 정규화)
    rotation_.x = fmod(rotation_.x, 360.0f);
    if (rotation_.x < 0.0f) rotation_.x += 360.0f;

    rotation_.y = fmod(rotation_.y, 360.0f);
    if (rotation_.y < 0.0f) rotation_.y += 360.0f;

    rotation_.z = fmod(rotation_.z, 360.0f);
    if (rotation_.z < 0.0f) rotation_.z += 360.0f;
}

void ModelMatrix::rotateZ(float deltaAngleZ) {
    rotation_.z += deltaAngleZ;

    // z축 각도 제한 (360도로 정규화)
    rotation_.z = fmod(rotation_.z, 360.0f);
    if (rotation_.z < 0.0f) rotation_.z += 360.0f;
}

float ModelMatrix::getYaw() const
{
    glm::vec3 f = getForwardVector();
    if (glm::length(f) < 0.f) {
        return 0.0f;
    }
    return glm::degrees(atan2(f.z, f.x));
}

void ModelMatrix::rotateX(float deltaAngleX) {
    rotation_.x += deltaAngleX;

    // x축 각도 제한 (360도로 정규화)
    rotation_.x = fmod(rotation_.x, 360.0f);
    if (rotation_.x < 0.0f) rotation_.x += 360.0f;
}

void ModelMatrix::rotateY(float deltaAngleY) {
    rotation_.y += deltaAngleY;

    // y축 각도 제한 (360도로 정규화)
    rotation_.y = fmod(rotation_.y, 360.0f);
    if (rotation_.y < 0.0f) rotation_.y += 360.0f;
}

// Scale
glm::vec3 ModelMatrix::getScale() const { return scale_; }
float ModelMatrix::getScaleX() const { return scale_.x; }
float ModelMatrix::getScaleY() const { return scale_.y; }
float ModelMatrix::getScaleZ() const{return scale_.z;}

void ModelMatrix::setScale(const glm::vec3& newScale) { scale_ = newScale; }
void ModelMatrix::setScaleX(float newX) {	scale_.x = newX; }
void ModelMatrix::setScaleY(float newY) {	scale_.y = newY;}
void ModelMatrix::setScaleZ(float newZ) { scale_.z = newZ;}

void ModelMatrix::scale(const glm::vec3& deltaScale){ scale_ += deltaScale;}
void ModelMatrix::scaleX(float deltaX){ scale_.x += deltaX;}
void ModelMatrix::scaleY(float deltaY){ scale_.y += deltaY;}
void ModelMatrix::scaleZ(float deltaZ){ scale_.z += deltaZ;}

void ModelMatrix::resetAll()
{
    rotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
    location_ = glm::vec3(0.0f, 0.f, 0.f);
    scale_ = glm::vec3(1.f, 1.f, 1.f);
}

void ModelMatrix::resetLocationRotation()
{
    rotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
    location_ = glm::vec3(0.0f, 0.f, 0.f);
}

void ModelMatrix::setPivot(float x, float y, float z)
{
    if (pivotPoint_) {
        delete pivotPoint_;
        pivotPoint_ = nullptr;
    }
    pivotPoint_ = new glm::vec3(x, y, z);
}

void ModelMatrix::setPivot(const glm::vec3& pivot)
{
    if (pivotPoint_) {
        delete pivotPoint_;
        pivotPoint_ = nullptr;
    }
    pivotPoint_ = new glm::vec3(pivot);
}

glm::mat4 ModelMatrix::getTransformMatrix() const
{
    glm::mat4 transform = glm::mat4(1.0f);
    if (parent_) {
        transform = parent_->getTransformMatrix();
    }
    transform = glm::translate(transform, location_);

    if (pivotPoint_) {
        transform = glm::translate(transform, *pivotPoint_);

        transform = glm::rotate(transform, glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));

        transform = glm::translate(transform, -*pivotPoint_);
    }

    else {
        transform = glm::rotate(transform, glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }

   

    transform = glm::scale(transform, scale_);
   
    return transform;
}

void ModelMatrix::setParent(ModelMatrix* parent)
{
    parent_ = parent;
}

void ModelMatrix::deleteParent()
{
    parent_ = nullptr;
}

glm::vec3 ModelMatrix::getForwardVector() const
{
    glm::mat4 tr = getTransformMatrix();
    glm::vec3 forward(tr[0][0], tr[0][1], tr[0][2]);
    return glm::normalize(forward);
}
