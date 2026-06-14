#include "User.h"

//Имплементация на User
User::User(unsigned int id, const std::string& uname, const std::string& pass)
	: userId(id), username(uname), password(pass) {}

unsigned int User::getId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const {
	return password;
}

bool User::checkPassword(const std::string& pass) const {
	return password == pass;
}

//Имплементация на Admin
Admin::Admin(unsigned int id, const std::string& uname, const std::string& pass)
	: User(id, uname, pass) {}
//Конструктора на базовия клас

void Admin::help() const {
	std::cout << "=== Admin Commands ===\n"
			  << " - block-user <username>\n"
			  << " - create-fragrance <name> <brand> <price> <family>\n"
			  << " - add-quantity <fragrance-name> <quantity>\n"
			  << " - deliver <purchase-id>\n"
			  << " - remove-review <fragrance-id> <review-id>\n";
}