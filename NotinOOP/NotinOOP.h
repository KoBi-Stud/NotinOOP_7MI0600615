#pragma once
#include <vector>
#include <memory>
#include <string>
#include "User.h"
#include "Customer.h"
#include "Fragrance.h"
#include "Purchase.h"

class NotinOOP {
private:
	//Всички потребители
	std::vector<std::unique_ptr<User>> users;

	//Данни за магазина
	std::vector<Fragrance> catalog;
	std::vector<std::shared_ptr<Purchase>> allPurchases;

	//Текущ потребител
	User* currentUser;

	//Помощни методи
	Fragrance* findFragrance(const std::string& name);
	Customer* getLoggedInCustomer() const;
	Admin* getLoggedInAdmin() const;

	//Помомщни функции за checout
	double calculateTotal(Customer* customer, std::vector<Fragrance>& itemsToPurchase);
	//Смята цена (с ваучери)
	void updateStockAndClearCart(Customer* customer, const std::vector<Fragrance>& items);
	//Обновява складови наличности и записва поръчка.

	//Помощна функция за препоръките - намира коя е любимата нотка
	FragranceFamily findFavoriteFamily(const Customer* customer);
	//Главната функция филтрира каталога (намира парфюми по тази нотка).


public:
	NotinOOP();

	//Главен метод за стартиране на конзолата
	void run();

	//Oбщи потребителски команди
	void registerUser(const std::string& username, const std::string& password);
	void login(const std::string& username, const std::string& password);
	void logout();

	//Команди на kупувача
	void checkout();
	void cancelPurchase(unsigned int purchaseId);
	void makeReview(const std::string& fragName, unsigned short rating, const std::string& comment);
	void recommend();

	//Команди на aдминистратора
	void blockUser(const std::string& username);
	void createFragrance(const std::string& name, Brand brand, double price, FragranceFamily family);
	void addQuantity(const std::string& name, unsigned int q);
	void deliverPurchase(unsigned int purchaseId);
	void removeReview(unsigned int fragId, unsigned int reviewId);

	//Работа с файлове
	void loadDatabase();
	void saveDatabase();
};