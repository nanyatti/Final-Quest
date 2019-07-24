#pragma once

/*!
* @brief 各オブジェクトの基底となる抽象クラス
*/
class AbstructObject {

protected:

	// 数値と向きの対応づけ
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