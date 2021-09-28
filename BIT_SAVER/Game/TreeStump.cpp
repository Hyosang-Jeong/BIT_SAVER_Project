/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TreeStump.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/15/2021
-----------------------------------------------------------------*/

#include "TreeStump.h"

TreeStump::TreeStump(math::vec2 pos, int size) : GameObject(pos) {
	switch (size) {
	case 1:
		AddGOComponent(new CS230::Sprite("assets/treeStump1.spt",this));
		break;													
	case 2:														
		AddGOComponent(new CS230::Sprite("assets/treeStump2.spt",this));
		break;													
	case 3:														
		AddGOComponent(new CS230::Sprite("assets/treeStump3.spt",this));
		break;													
	case 5:														
		AddGOComponent(new CS230::Sprite("assets/treeStump5.spt",this));
		break;
	}
}

