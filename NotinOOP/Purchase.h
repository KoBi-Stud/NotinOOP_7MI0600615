#pragma once
#include <vector>
#include <iostream>
#include "Fragrance.h"
#include "Enums.h"

class Purchase {
private:
	unsigned int purchaseId;
	unsigned int userId;

	//Списък от парфюмите
	std::vector<Fragrance> fragrances;

	OrderState state;

	//Запазваме крайната цена, за да не се променя, ако цените в магазина се вдигнат утре.
	double finalPrice;

public:
	Purchase(unsigned int pId, unsigned int uId, const std::vector<Fragrance>& items, double price);

	//Get-ъри
	unsigned int getId() const;
	unsigned int getUserId() const;
	OrderState getState() const;
	double getFinalPrice() const;
	const std::vector<Fragrance>& getFragrances() const;

	//Промяна на състоянието
	bool deliver();
	//Прави състоянието DELIVERED
	bool cancel();
	//Прави състоянието CANCELED

	//Методът от условието
	void show() const;

	//Помощен метод за превръщане на състоянието в текст
	std::string stateToString() const;
};