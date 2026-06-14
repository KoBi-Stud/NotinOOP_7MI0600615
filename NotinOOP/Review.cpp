#include "Review.h"
#include <iostream>

//Конструктор
Review::Review(unsigned int id, const std::string& fragName, unsigned int uId, const std::string& comm, unsigned short r)
	: reviewId(id), fragranceName(fragName), userId(uId) {

	//Валидация на коментара (до 1000 символа според условието)
	if (comm.length() > 1000) {
		comment = comm.substr(0, 1000); //Режем го до 1000
	} else {
		comment = comm;
	}

	//Валидация на рейтинга (хвърляме exception)
	if (r > 5) {
		throw std::invalid_argument("Rating must be between 0 and 5!");
	}
	rating = r;
}

//Get-ъри
unsigned int Review::getId() const { return reviewId; }
std::string Review::getFragranceName() const { return fragranceName; }
unsigned int Review::getUserId() const { return userId; }
std::string Review::getComment() const { return comment; }
unsigned short Review::getRating() const { return rating; }

void Review::print() const {
	std::cout << "[Review ID: " << reviewId << " | User ID: " << userId << "]\n"
			  << "Rating: " << rating << "/5\n"
			  << "Comment: " << comment << "\n";
}