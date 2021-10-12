/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformMatrix.cpp
Project: BIT_SAVER
Author: 
Creation date: 3/28/2021
-----------------------------------------------------------------*/
#include"TransformMatrix.h"

math::TransformMatrix::TransformMatrix()
{
    Reset();
}

void math::TransformMatrix::Reset()
{
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 0;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
}
math::TranslateMatrix::TranslateMatrix(math::ivec2 translate)
{
    matrix[0][2] += translate.x;
    matrix[1][2] += translate.y;
}
math::TranslateMatrix::TranslateMatrix(glm::vec2 translate)
{
    matrix[0][2] += translate.x;
    matrix[1][2] += translate.y;
}

math::TransformMatrix math::TransformMatrix::operator * (TransformMatrix rhs) const {
    TransformMatrix result;

    result.matrix[0][0] = matrix[0][0] * rhs[0][0] + matrix[0][1] * rhs[1][0] + matrix[0][2] * rhs[2][0];
    result.matrix[0][1] = matrix[0][0] * rhs[0][1] + matrix[0][1] * rhs[1][1] + matrix[0][2] * rhs[2][1];
    result.matrix[0][2] = matrix[0][0] * rhs[0][2] + matrix[0][1] * rhs[1][2] + matrix[0][2] * rhs[2][2];
    result.matrix[1][0] = matrix[1][0] * rhs[0][0] + matrix[1][1] * rhs[1][0] + matrix[1][2] * rhs[2][0];
    result.matrix[1][1] = matrix[1][0] * rhs[0][1] + matrix[1][1] * rhs[1][1] + matrix[1][2] * rhs[2][1];
    result.matrix[1][2] = matrix[1][0] * rhs[0][2] + matrix[1][1] * rhs[1][2] + matrix[1][2] * rhs[2][2];
    result.matrix[2][0] = matrix[2][0] * rhs[0][0] + matrix[2][1] * rhs[1][0] + matrix[2][2] * rhs[2][0];
    result.matrix[2][1] = matrix[2][0] * rhs[0][1] + matrix[2][1] * rhs[1][1] + matrix[2][2] * rhs[2][1];
    result.matrix[2][2] = matrix[2][0] * rhs[0][2] + matrix[2][1] * rhs[1][2] + matrix[2][2] * rhs[2][2];

    return result;
}

math::TransformMatrix& math::TransformMatrix::operator *= (math::TransformMatrix rhs) {
    (*this) = (*this) * rhs;
    return (*this);
}

math::RotateMatrix::RotateMatrix(double radians)
{
    matrix[0][0] = cos(radians);
    matrix[0][1] = -sin(radians);
    matrix[1][0] = sin(radians);
    matrix[1][1] = cos(radians);
}

math::ScaleMatrix::ScaleMatrix(glm::vec2 scale)
{
    matrix[0][0] = scale.x;
    matrix[1][1] = scale.y;
}

math::vec2 math::TransformMatrix::operator * (math::vec2 rhs) const {
    math::vec2 result;
    result.x = matrix[0][0] * rhs.x + matrix[0][1] * rhs.y + matrix[0][2];
    result.y = matrix[1][0] * rhs.x + matrix[1][1] * rhs.y + matrix[1][2];
    return result;
}