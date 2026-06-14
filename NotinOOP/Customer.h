#pragma once
#include "User.h"
#include "Purchase.h"
#include "Discount.h"
#include <vector>
#include <memory> // За std::unique_ptr

class Customer : public User {
private:
    double balance;

    //Пазим имената на парфюмите (или ID) за количката и любимите
    std::vector<std::string> cart;
    std::vector<std::string> wishlist;

    //История на поръчките
	std::vector<std::shared_ptr<Purchase>> purchases;

    //Ваучерите (Умни указатели към базовия клас)
    std::vector<std::unique_ptr<Discount>> discounts;

public:
    Customer(unsigned int id, const std::string& uname, const std::string& pass);

    //unique_ptr не може да се копира директно
    Customer(const Customer&) = delete;
    Customer& operator=(const Customer&) = delete;

    //Move semantics
    Customer(Customer&&) = default;
    Customer& operator=(Customer&&) = default;

    //Пренаписваме help() за купувача
    void help() const override;

    //Управление на профила
    double getBalance() const;
    void addToBalance(double amount);

    //Количка и любими
    void addToWishlist(const std::string& fragranceName);
    void removeFromWishlist(const std::string& fragranceName);
    const std::vector<std::string>& getWishlist() const;

    void addToCart(const std::string& fragranceName);
    void removeFromCart(const std::string& fragranceName);
    void viewCart() const;
    void clearCart();
	//Извиква се след успешно плащане

    //Ваучери
    //Подаваме ваучера чрез move, защото сменя собственика си
    void addDiscount(std::unique_ptr<Discount> discount);

    //Показва всички налични ваучери
    void viewDiscounts() const;

	const std::vector<std::unique_ptr<Discount>>& getDiscounts() const;
	void clearDiscounts();
	//Трием, след като са използвани


    //История
    void addPurchase(std::shared_ptr<Purchase> purchase);
	//Добавя поръчка към историята
    void viewBought() const;
	//Показва само успешни
    void viewPurchases() const;
	//Показва всички

	const std::vector<std::string>& getCart() const;
	bool pay(double amount);
	//Метод за плащане
};