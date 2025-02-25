#pragma once

/*!
* @brief DXライブラリやゲームの準備
*/
class SystemMain {

public:

	SystemMain() {}
	~SystemMain() {}
	bool Initialize() const;
	void Finalize() const;
	void Main() const;
};