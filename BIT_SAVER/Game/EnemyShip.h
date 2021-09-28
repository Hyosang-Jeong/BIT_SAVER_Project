/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyShip.h
Project: CS230
Author: Kevin Wright
Creation date: 6/14/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameObject.h"
#include "..\Engine\Sprite.h"

class EnemyShip : public CS230::GameObject {
public:
    EnemyShip(GameObject* player);
    void Update(double dt);
    void Draw(math::TransformMatrix displayMatrix);

    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;
    bool CanCollideWith(GameObjectType collideAgainstType) override;
    void ResolveCollision(GameObject* collidedWith);

    bool IsDead() { return isDead; }
private:
    GameObject* player;
    CS230::Sprite flameLeft;
    CS230::Sprite flameRight;
    bool isDead;

    static constexpr double accel = 200;
    static constexpr double drag = 1;
    static constexpr double rotationRate = 3;
};

