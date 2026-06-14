#include "Customer.h"
#include <algorithm>

Customer::Customer(unsigned int id, const std::string& uname, const std::string& pass)
    : User(id, uname, pass), balance(0.0) {}

void Customer::help() const {
    std::cout << "=== Customer Commands ===\n"
              << " - add-to-balance <amount>\n"
              << " - add-to-cart <name> | remove-from-cart <name> | view-cart\n"
              << " - add-to-wishlist <name> | remove-from-wishlist <name>\n"
              << " - checkout | cancel <purchase-id>\n"
              << " - view-bought | view-purchases\n"
              << " - recommend\n"
              << " - make-review <name> <rating> <comment>\n";
}

double Customer::getBalance() const { return balance; }

void Customer::addToBalance(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

//Количка
void Customer::addToCart(const std::string& fragranceName) {
    cart.push_back(fragranceName);
}

void Customer::removeFromCart(const std::string& fragranceName) {
    auto it = std::find(cart.begin(), cart.end(), fragranceName);
    if (it != cart.end()) {
        cart.erase(it);
    }
}

void Customer::viewCart() const {
    std::cout << "--- Your Cart ---\n";
    if (cart.empty()) std::cout << "Cart is empty.\n";
    for (const auto& item : cart) {
        std::cout << " - " << item << "\n";
    }
}

void Customer::clearCart() {
    cart.clear();
}


//Любими (Wishlist)

void Customer::addToWishlist(const std::string& fragranceName) {
	// Проверяваме дали вече не е добавен, за да няма дубликати
	if (std::find(wishlist.begin(), wishlist.end(), fragranceName) == wishlist.end()) {
		wishlist.push_back(fragranceName);
	}
}

void Customer::removeFromWishlist(const std::string& fragranceName) {
	auto it = std::find(wishlist.begin(), wishlist.end(), fragranceName);
	if (it != wishlist.end()) {
		wishlist.erase(it);
	}
}

const std::vector<std::string>& Customer::getWishlist() const {
	return wishlist;
}


//Ваучери
//Използваме std::move, за да прехвърлим собствеността на умния указател в нашия вектор
void Customer::addDiscount(std::unique_ptr<Discount> discount) {
    discounts.push_back(std::move(discount));
}

void Customer::viewDiscounts() const {
    std::cout << "--- Your Discounts ---\n";
    for (const auto& d : discounts) {
        d->print();
    	//Полиморфизъм
    }
}

const std::vector<std::unique_ptr<Discount>>& Customer::getDiscounts() const {
	return discounts;
}

void Customer::clearDiscounts() {
	discounts.clear();
}

//История на поръчките
void Customer::addPurchase(std::shared_ptr<Purchase> purchase) {
	purchases.push_back(purchase);
}

void Customer::viewBought() const {
	std::cout << "--- Successful Purchases ---\n";
	for (const auto& p : purchases) {
		if (p->getState() == OrderState::DELIVERED) {
			p->show();
		}
	}
}

void Customer::viewPurchases() const {
	std::cout << "--- All Purchase History ---\n";
	for (const auto& p : purchases) {
		p->show();
	}
}


const std::vector<std::string>& Customer::getCart() const {
	return cart;
}

bool Customer::pay(double amount) {
	if (balance >= amount) {
		balance -= amount;
		return true;
	}
	return false;
}