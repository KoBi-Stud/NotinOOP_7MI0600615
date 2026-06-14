#include "Discount.h"
#include <algorithm> // За std::max

//Имплементация на базовия клас Discount
Discount::Discount(unsigned int id, double percent)
    : discountId(id), discountPercent(percent) {}

unsigned int Discount::getId() const { return discountId; }
double Discount::getPercent() const { return discountPercent; }

double Discount::apply(const Fragrance& item, double currentPrice) const {
    //Използваме item само за съвместимост с наследниците
    double discountAmount = currentPrice * (discountPercent / 100.0);
    return currentPrice - discountAmount;
}

void Discount::print() const {
    std::cout << "[Discount ID: " << discountId << "] Standard: " << discountPercent << "% off\n";
}

//Имплементация на BonusDiscount
BonusDiscount::BonusDiscount(unsigned int id, double percent, double b)
    : Discount(id, percent), bonus(b) {}

double BonusDiscount::apply(const Fragrance& item, double currentPrice) const {
    //Прилагаме процентното намаление от базовия клас
    double priceAfterPercent = Discount::apply(item, currentPrice);

    //След това вадим твърдия бонус
    double finalPrice = priceAfterPercent - bonus;

    //Ако цената падне под 0, я правим 0
    return std::max(0.0, finalPrice);
}

void BonusDiscount::print() const {
    std::cout << "[Discount ID: " << getId() << "] Bonus: "
              << getPercent() << "% off + $" << bonus << " flat deduction\n";
}

//Имплементация на BrandDiscount
BrandDiscount::BrandDiscount(unsigned int id, double percent, Brand b)
    : Discount(id, percent), targetBrand(b) {}

double BrandDiscount::apply(const Fragrance& item, double currentPrice) const {
    //Проверяваме дали парфюмът е от промоционалната марка
    if (item.getBrand() == targetBrand) {
        // Ако да, прилагаме намалението
        return Discount::apply(item, currentPrice);
    }

    // Ако не, връщаме цената без промяна
    return currentPrice;
}

void BrandDiscount::print() const {
    std::cout << "[Discount ID: " << getId() << "] Brand Specific: "
              << getPercent() << "% off on " << brandToString(targetBrand) << " only\n";
}