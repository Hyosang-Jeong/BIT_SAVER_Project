/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Component.h
Purpose: This is the service provider for our games engine services
Project: BIT_SAVER
Author:
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once

class Component {
public:
    virtual ~Component() {};
    virtual void Update(double) {};
};