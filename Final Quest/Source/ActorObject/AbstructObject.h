#pragma once

/*!
* @brief �e�I�u�W�F�N�g�̊��ƂȂ钊�ۃN���X
*/
class AbstructObject {

protected:

	// ���l�ƌ����̑Ή��Â�
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

public:

	AbstructObject() {}
	virtual ~AbstructObject() {}
	virtual void Update() = 0;
	virtual void Draw() const = 0;
};