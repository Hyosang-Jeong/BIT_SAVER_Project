/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformMatrix.h
Project: BIT_SAVER
Author: 
Creation date: 2/12/2021
-----------------------------------------------------------------*/
#pragma once
#include "Vec2.h"  // vec2, ivec2 struct
#include<glm/glm.hpp>
namespace math {
    class TransformMatrix 
    {
    public:
        TransformMatrix();

        const double* operator[](int index) const { return matrix[index]; }
        TransformMatrix operator * (TransformMatrix rhs) const;
        TransformMatrix& operator *= (TransformMatrix rhs);
        vec2 operator * (vec2 rhs) const;
        void Reset();
    protected:
        double matrix[3][3];
    };

    class TranslateMatrix : public TransformMatrix {
    public:
        TranslateMatrix(ivec2 translate);
        TranslateMatrix(glm::vec2 translate);
    };

    class RotateMatrix : public TransformMatrix {
    public:
        RotateMatrix(double radians);
    };

    class ScaleMatrix : public TransformMatrix {
    public:
        ScaleMatrix(glm::vec2 scale);
    };

}

