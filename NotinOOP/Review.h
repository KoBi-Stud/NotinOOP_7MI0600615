#pragma once
#include <string>
#include <stdexcept>

class Review {
private:
	unsigned int reviewId;
	std::string fragranceName;
	unsigned int userId;
	std::string comment;
	unsigned short rating; //число от 0 до 5

public:
	//Конструктор
	Review(unsigned int id, const std::string& fragName, unsigned int uId, const std::string& comm, unsigned short r);

	//Get-ъри
	unsigned int getId() const;
	std::string getFragranceName() const;
	unsigned int getUserId() const;
	std::string getComment() const;
	unsigned short getRating() const;

	//Метод за принтване
	void print() const;
};