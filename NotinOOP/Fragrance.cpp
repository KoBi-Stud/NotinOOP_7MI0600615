#include "Fragrance.h"
#include <iostream>
#include <algorithm> // За std::remove_if

Fragrance::Fragrance(unsigned int id, const std::string& n, Brand b, double p, FragranceFamily f, unsigned int q)
    : fragranceId(id), name(n), brand(b), price(p), family(f), quantity(q) {
}

//Get-ъри
unsigned int Fragrance::getId() const { return fragranceId; }
std::string Fragrance::getName() const { return name; }
Brand Fragrance::getBrand() const { return brand; }
double Fragrance::getPrice() const { return price; }
FragranceFamily Fragrance::getFamily() const { return family; }
unsigned int Fragrance::getQuantity() const { return quantity; }

const std::vector<Review>& Fragrance::getReviews() const {
    return reviews;
}

void Fragrance::addQuantity(unsigned int q) {
    quantity += q;
}

bool Fragrance::reduceQuantity(unsigned int q) {
    if (quantity >= q) {
        quantity -= q;
        return true;
    }
    return false; //Ако няма достатъчно наличност
}

void Fragrance::addReview(const Review& review) {
    reviews.push_back(review);
}

//Премахване на ревю по ID (нужно за администратора)
bool Fragrance::removeReview(unsigned int reviewId) {
    //remove_if за търсене и триене във вектор
    auto it = std::remove_if(reviews.begin(), reviews.end(),
        [reviewId](const Review& r) { return r.getId() == reviewId; });

    if (it != reviews.end()) {
        reviews.erase(it, reviews.end());
        return true;
    	//Ревюто е намерено и изтрито
    }
    return false;
	//Ревюто не съществува
}

//Пресмятане на среден рейтинг
double Fragrance::getRating() const {
    if (reviews.empty()) {
        return 0.0;
    	//Ако няма ревюта, връщаме 0
    }

    double sum = 0.0;
    for (const Review& r : reviews) {
        sum += r.getRating();
    }

    return sum / reviews.size();
}

void Fragrance::print() const {
    std::cout << "--- Fragrance [" << fragranceId << "] ---\n"
              << "Name: " << name << "\n"
              << "Brand: " << brandToString(brand) << "\n"
              << "Price: $" << price << "\n"
              << "Quantity in stock: " << quantity << "\n"
              << "Average Rating: " << getRating() << "/5.0 (" << reviews.size() << " reviews)\n"
              << "-------------------------\n";
}