/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ComponentManager.h
Purpose: This is the service provider for our games engine services
Project: BIT_SAVER
Author:
Creation date: 2/10/2021
-----------------------------------------------------------------*/

#pragma once
#include <algorithm>
#include <vector>
#include <memory>
#include "Component.h"

class ComponentManager {
public:
    ~ComponentManager() {
        Clear();
    }
    void UpdateAll(double dt) {
        for (Component* component : components) 
        {
            component->Update(dt);
        }
    }

    template<typename T>
    T* GetComponent() {
        for (Component* component : components) {
            T* ptr = dynamic_cast<T*>(component);
            if (ptr != nullptr) {
                return ptr;
            }
        }
        return nullptr;
    }

    void AddComponent(Component* component) {
        components.push_back(component);
    }
    template<typename T>
    void RemoveComponent() {
        auto it = std::find_if(components.begin(), components.end(), [](Component* element) {
            return (dynamic_cast<T*>(element) != nullptr);
            });
        delete* it;
        components.erase(it);
    }
    void Clear() {
        for (Component* component : components) {
            delete component;
        }
        components.clear();
    }
private:
    std::vector<Component*> components;
};