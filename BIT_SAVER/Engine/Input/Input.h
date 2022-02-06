/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.h
Project: BIT_SAVER
Author: Hyosang Jung 

-----------------------------------------------------------------*/
#pragma once
#include <vector>
#include <glm/glm.hpp>
	class InputKey 
	{
	public:
		enum class Keyboard
		{
			None, Enter, Escape, Space, Left, Up, Right, Down,
			A, B, C, D, E, F, G, H, I, J,
			K, L, M, N, O, P, Q, R, S, T,
			U, V, W, X, Y, Z, NUM_0, NUM_1, NUM_2, NUM_3,
			Tilde,
			Count
		};
		enum class Mouse {
		    None, Left, Count
		};

		InputKey(Keyboard button);
		InputKey(Mouse mouseButton);

		bool MouseIsKeyDown() const;
		bool MouseIsKeyReleased() const;
		bool MouseIsKeyReapeated() const;

		bool IsKeyDown() const;
		bool IsKeyReleased() const;
		bool IsKeyReapeated() const;

		Keyboard button;
		Mouse mouseButton;
	};

	class Input
	{
	public:
		Input();
		bool IsKeyDown(InputKey::Keyboard key) const;
		bool IsKeyReleased(InputKey::Keyboard key) const;
		bool IsKeyReapeated(InputKey::Keyboard key) const;
		void SetKeyDown(InputKey::Keyboard key, bool value);
		void SetLastpressedButton(InputKey::Keyboard key);
		void Update();

		bool MouseIsKeyDown(InputKey::Mouse key) const;
		bool MouseIsKeyReleased(InputKey::Mouse key) const;
		bool MouseIsKeyReapeated(InputKey::Mouse key) const;
		void MouseSetKeyDown(InputKey::Mouse key, bool value);

		void MouseSetPosition(glm::vec2 newPosition);

		glm::vec2 MouseGetPosition() const;

		void MouseUpdate();
		InputKey::Keyboard GetLastPressedButton();
	private:
		std::vector<bool> keyDown;
		std::vector<bool> wasKeyDown;

		std::vector<bool> mouseKeyDown;
		std::vector<bool> mouseWasKeyDown;
		glm::vec2 mousePosition;
		InputKey::Keyboard button;
	};

	struct AttackKey
	{
		AttackKey() :UpAttackKey(InputKey::Keyboard::None), DownAttackKey(InputKey::Keyboard::None) {};
	public:
		InputKey UpAttackKey;
		InputKey DownAttackKey;
	};
