#ifndef _USER_MANAGER_H_H_
#define _USER_MANAGER_H_H_

#include <string>

using namespace std;

class UserManager
{
public:
	static UserManager* getInstance();

	void Release();

	void Clear();

	int GetScore() const;
	int GetStage() const;
	int GetStageMax() const;
	int GetLife() const;
	string GetOwn() const;

	void SetScore(const int& score);
	void SetStage(const int& stage);
	void SetStageMax(const int& stageMax);
	void SetLife(const int& life);
	void SetOwn(const string& ownName);

private:
	UserManager()
	: _score(0)
	, _stage(0)
	, _stageMax(0)
	, _ownName("")
	{}

	UserManager(UserManager&);
	UserManager& operator=(UserManager&);

private:
	int _score;
	int _stage;
	int _stageMax;
	int _life;
	string _ownName;
};

#endif