#pragma once
#include <string>
#include <iostream>

//Базов абстрактен клас
class User {
protected:
	unsigned int userId;
	std::string username;
	std::string password;

public:
	User(unsigned int id, const std::string& uname, const std::string& pass);
	virtual ~User() = default;
	//Задължително за полиморфизъм

	//Get-ъри
	unsigned int getId() const;
	std::string getUsername() const;
	std::string getPassword() const;

	//Проверка на парола при login
	bool checkPassword(const std::string& pass) const;

	//Чисто виртуална функция
	virtual void help() const = 0;
};

//Наследник 1: Администратор
class Admin : public User {
public:
	Admin(unsigned int id, const std::string& uname, const std::string& pass);

	//Пренаписваме help() за администратора
	void help() const override;
};