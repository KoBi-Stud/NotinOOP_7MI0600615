#pragma once
#include <string>
#include <vector>
#include "Enums.h"
#include "Review.h"

class Fragrance {
private:
	unsigned int fragranceId;
	std::string name;
	Brand brand;
	double price;
	FragranceFamily family;
	unsigned int quantity;

	//Списък от ревюта
	std::vector<Review> reviews;

public:
	Fragrance(unsigned int id, const std::string& n, Brand b, double p, FragranceFamily f, unsigned int q);

	//Get-ъри
	unsigned int getId() const;
	std::string getName() const;
	Brand getBrand() const;
	double getPrice() const;
	FragranceFamily getFamily() const;
	unsigned int getQuantity() const;
	const std::vector<Review>& getReviews() const;

	//Set-ъри
	void addQuantity(unsigned int q);
	bool reduceQuantity(unsigned int q);
	//Връща true, ако има достатъчно бройки и са намалени

	//Управление на ревютата
	void addReview(const Review& review);
	bool removeReview(unsigned int reviewId);
	//Връща true, ако е намерено и изтрито

	//Метод от условието
	double getRating() const;

	//Помощен метод за принтване
	void print() const;
};