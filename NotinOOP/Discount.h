#pragma once
#include "Fragrance.h"
#include <iostream>

//Базов клас
class Discount {
private:
	unsigned int discountId;
	double discountPercent;

public:
	Discount(unsigned int id, double percent);

	//Виртуален деструктор (заради полимор)
	virtual ~Discount() = default;

	unsigned int getId() const;
	double getPercent() const;

	//Виртуална функция за прилагане на намалението
	//Приема парфюма (за да провери марката, ако трябва) и текущата му цена
	//Връща новата цена след намалението
	virtual double apply(const Fragrance& item, double currentPrice) const;

	//Виртуална функция за принтиране
	virtual void print() const;
};

//Първи наследник: BonusDiscount
class BonusDiscount : public Discount {
private:
	double bonus; //Точна сума за допълнително приспадане

public:
	BonusDiscount(unsigned int id, double percent, double b);

	double apply(const Fragrance& item, double currentPrice) const override;
	void print() const override;
};

//Втори наследник: BrandDiscount
class BrandDiscount : public Discount {
private:
	Brand targetBrand; //За коя марка важи

public:
	BrandDiscount(unsigned int id, double percent, Brand b);

	double apply(const Fragrance& item, double currentPrice) const override;
	void print() const override;
};