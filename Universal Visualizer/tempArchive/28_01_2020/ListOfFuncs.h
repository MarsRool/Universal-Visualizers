#pragma once
class ListOfFuncs
{
private:
	std::vector<char *> names;
	std::vector<char **> Funcs;
public:
	ListOfFuncs();
	void AddFunc(char* namei, char **Funcs_i);
	void Clear();
	char* GetName(int k);
};