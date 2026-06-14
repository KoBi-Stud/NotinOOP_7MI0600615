#include "NotinOOP.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <map>
#include <fstream>

NotinOOP::NotinOOP() : currentUser(nullptr) {
    // Автоматично генериран админ при първо пускане
    users.push_back(std::make_unique<Admin>(0, "admin", "admin123"));
}

Customer* NotinOOP::getLoggedInCustomer() const {
    return dynamic_cast<Customer*>(currentUser);
}

Admin* NotinOOP::getLoggedInAdmin() const {
    return dynamic_cast<Admin*>(currentUser);
}

Fragrance* NotinOOP::findFragrance(const std::string& name) {
    for (auto& f : catalog) {
        if (f.getName() == name) return &f;
    }
    return nullptr;
}


void NotinOOP::run() {
    loadDatabase();
    std::cout << "Welcome to NotinOOP! Type 'help' for commands.\n";
    std::string command;

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "end") {
            saveDatabase();
            std::cout << "System shutting down. Goodbye!\n";
            break;
        }
        else if (command == "register") {
            std::string user, pass; std::cin >> user >> pass;
            registerUser(user, pass);
        }
        else if (command == "login") {
            std::string user, pass; std::cin >> user >> pass;
            login(user, pass);
        }
        else if (command == "logout") { logout(); }
        else if (command == "help") {
            if (currentUser) currentUser->help();
            else std::cout << "Available: login, register, end\n";
        }
        else if (command == "add-to-balance") {
            double amount; std::cin >> amount;
            if (auto* c = getLoggedInCustomer()) c->addToBalance(amount);
            else std::cout << "Access denied.\n";
        }
        else if (command == "add-to-cart") {
            std::string name; std::cin >> name;
            if (auto* c = getLoggedInCustomer()) c->addToCart(name);
            else std::cout << "Access denied.\n";
        }
        else if (command == "remove-from-cart") {
            std::string name; std::cin >> name;
            if (auto* c = getLoggedInCustomer()) c->removeFromCart(name);
            else std::cout << "Access denied.\n";
        }
        else if (command == "view-cart") {
            if (auto* c = getLoggedInCustomer()) c->viewCart();
            else std::cout << "Access denied.\n";
        }
        else if (command == "add-to-wishlist") {
            std::string name; std::cin >> name;
            if (auto* c = getLoggedInCustomer()) c->addToWishlist(name);
            else std::cout << "Access denied.\n";
        }
        else if (command == "remove-from-wishlist") {
            std::string name; std::cin >> name;
            if (auto* c = getLoggedInCustomer()) c->removeFromWishlist(name);
            else std::cout << "Access denied.\n";
        }
        else if (command == "checkout") { checkout(); }
        else if (command == "cancel") {
            unsigned int pId; std::cin >> pId;
            cancelPurchase(pId);
        }
        else if (command == "view-bought") {
            if (auto* c = getLoggedInCustomer()) c->viewBought();
            else std::cout << "Access denied.\n";
        }
        else if (command == "view-purchases") {
            if (auto* c = getLoggedInCustomer()) c->viewPurchases();
            else std::cout << "Access denied.\n";
        }
        else if (command == "make-review") {
            std::string name; unsigned short rating; std::string comment;
            std::cin >> name >> rating;
            std::getline(std::cin >> std::ws, comment);
            makeReview(name, rating, comment);
        }
        else if (command == "recommend") { recommend(); }
        else if (command == "block-user") {
            std::string targetUser; std::cin >> targetUser;
            blockUser(targetUser);
        }
        else if (command == "create-fragrance") {
            std::string name; int brandInt; double price; int familyInt;
            std::cin >> name >> brandInt >> price >> familyInt;
            createFragrance(name, static_cast<Brand>(brandInt), price, static_cast<FragranceFamily>(familyInt));
        }
        else if (command == "add-quantity") {
            std::string name; unsigned int q; std::cin >> name >> q;
            addQuantity(name, q);
        }
        else if (command == "deliver") {
            unsigned int pId; std::cin >> pId;
            deliverPurchase(pId);
        }
        else if (command == "remove-review") {
            unsigned int fId, rId; std::cin >> fId >> rId;
            removeReview(fId, rId);
        }
        else {
            std::cout << "Unknown command!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

//Логика за потребител
void NotinOOP::registerUser(const std::string& username, const std::string& password) {
    for (const auto& u : users) {
        if (u->getUsername() == username) {
            std::cout << "Username already exists!\n"; return;
        }
    }
    unsigned int newId = users.size() + 1;
    users.push_back(std::make_unique<Customer>(newId, username, password));
    std::cout << "User " << username << " registered successfully!\n";
}

void NotinOOP::login(const std::string& username, const std::string& password) {
    if (currentUser) { std::cout << "Already logged in!\n"; return; }
    for (const auto& u : users) {
        if (u->getUsername() == username && u->checkPassword(password)) {
            currentUser = u.get();
            std::cout << "Logged in as " << username << ".\n"; return;
        }
    }
    std::cout << "Invalid credentials.\n";
}

void NotinOOP::logout() {
    if (currentUser) {
        std::cout << "Logged out.\n";
        currentUser = nullptr;
    } else { std::cout << "Not logged in.\n"; }
}

double NotinOOP::calculateTotal(Customer* customer, std::vector<Fragrance>& itemsToPurchase) {
	double total = 0.0;
	for (const auto& itemName : customer->getCart()) {
		Fragrance* f = findFragrance(itemName);
		if (f && f->getQuantity() > 0) {
			double price = f->getPrice();
			// Тук логиката за ваучери стои чисто
			for (const auto& d : customer->getDiscounts()) {
				price = std::min(price, d->apply(*f, f->getPrice()));
			}
			total += price;
			itemsToPurchase.push_back(*f);
		}
	}
	return total;
}

void NotinOOP::checkout() {
	Customer* customer = getLoggedInCustomer();
	if (!customer) { std::cout << "Only customers can checkout!\n"; return; }

	std::vector<Fragrance> itemsToPurchase;
	double total = calculateTotal(customer, itemsToPurchase);

	if (itemsToPurchase.empty()) {
		std::cout << "Your cart is empty or items are out of stock!\n";
		return;
	}

	if (!customer->pay(total)) {
		std::cout << "Insufficient funds! Need $" << total << "\n";
		return;
	}

	updateStockAndClearCart(customer, itemsToPurchase);

	//Създаване на поръчката
	auto newPurchase = std::make_shared<Purchase>(allPurchases.size() + 1, customer->getId(), itemsToPurchase, total);
	allPurchases.push_back(newPurchase);
	customer->addPurchase(newPurchase);
	customer->clearDiscounts();

	std::cout << "Checkout successful! Paid: $" << total << "\n";
	std::cout << "Congratulations! You received a 15% discount voucher for your next purchase!\n";
}

void NotinOOP::updateStockAndClearCart(Customer* customer, const std::vector<Fragrance>& items) {
	for (const auto& item : items) {
		findFragrance(item.getName())->reduceQuantity(1);
	}
	customer->clearCart();
}

void NotinOOP::cancelPurchase(unsigned int purchaseId) {
	Customer* customer = getLoggedInCustomer();
	if (!customer) return;

	for (auto& p : allPurchases) {
		if (p->getId() == purchaseId && p->getUserId() == customer->getId()) {
			if (p->cancel()) {
				customer->addToBalance(p->getFinalPrice());
				std::cout << "Purchase canceled. Refunded: $" << p->getFinalPrice() << "\n";
			} else {
				std::cout << "Cannot cancel. Not PENDING.\n";
			}
			return;
		}
	}
	std::cout << "Purchase not found.\n";
}

void NotinOOP::makeReview(const std::string& fragName, unsigned short rating, const std::string& comment) {
    Customer* customer = getLoggedInCustomer();
    if (!customer) return;

    Fragrance* f = findFragrance(fragName);
    if (!f) { std::cout << "Fragrance not found!\n"; return; }

    try {
        static unsigned int reviewCounter = 1;
        Review newReview(reviewCounter++, fragName, customer->getId(), comment, rating);
        f->addReview(newReview);
        std::cout << "Review added.\n";
    } catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
}


FragranceFamily NotinOOP::findFavoriteFamily(const Customer* customer) {
	const auto& wishlist = customer->getWishlist();
	if (wishlist.empty()) return FragranceFamily::UNKNOWN;

	//Броим кои нотки присъстват най-много в списъка с желания
	std::map<FragranceFamily, int> counts;
	for (const auto& name : wishlist) {
		if (Fragrance* f = findFragrance(name)) {
			counts[f->getFamily()]++;
		}
	}

	//Намираме най-честата
	FragranceFamily best = FragranceFamily::UNKNOWN;
	int maxCount = 0;
	for (auto const& [family, count] : counts) {
		if (count > maxCount) {
			maxCount = count;
			best = family;
		}
	}
	return best;
}

void NotinOOP::recommend() {
	Customer* customer = getLoggedInCustomer();
	if (!customer) return;

	FragranceFamily fav = findFavoriteFamily(customer);
	if (fav == FragranceFamily::UNKNOWN) {
		std::cout << "Add more items to your wishlist to get recommendations!\n";
		return;
	}

	std::cout << "--- Recommended for you ---\n";
	for (const auto& f : catalog) {
		//Препоръчваме, ако е от същата нотка и не е в количката/желанията
		if (f.getFamily() == fav) {
			bool inWishlist = false;
			for(const auto& w : customer->getWishlist()) {
				if(w == f.getName()) inWishlist = true;
			}

			if (!inWishlist) {
				std::cout << "- " << f.getName() << " ($" << f.getPrice() << ")\n";
			}
		}
	}
}

//Логика за администратори
void NotinOOP::blockUser(const std::string& username) {
    Admin* admin = getLoggedInAdmin();
    if (!admin) { std::cout << "Admin privileges required!\n"; return; }
    if (username == currentUser->getUsername()) { std::cout << "Cannot block yourself!\n"; return; }

    auto it = std::remove_if(users.begin(), users.end(),
                             [&](const std::unique_ptr<User>& u) { return u->getUsername() == username; });

    if (it != users.end()) {
        users.erase(it, users.end());
        std::cout << "User " << username << " blocked.\n";
    } else { std::cout << "User not found.\n"; }
}

void NotinOOP::createFragrance(const std::string& name, Brand brand, double price, FragranceFamily family) {
    if (!getLoggedInAdmin()) { std::cout << "Admin privileges required!\n"; return; }
    if (findFragrance(name)) { std::cout << "Fragrance already exists.\n"; return; }

    catalog.emplace_back(catalog.size() + 1, name, brand, price, family, 0);
    std::cout << "Fragrance created.\n";
}

void NotinOOP::addQuantity(const std::string& name, unsigned int q) {
    if (!getLoggedInAdmin()) { std::cout << "Admin privileges required!\n"; return; }
    Fragrance* f = findFragrance(name);
    if (f) { f->addQuantity(q); std::cout << "Quantity updated.\n"; }
    else std::cout << "Fragrance not found.\n";
}

void NotinOOP::deliverPurchase(unsigned int purchaseId) {
	if (!getLoggedInAdmin()) { std::cout << "Admin privileges required!\n"; return; }

	for (auto& p : allPurchases) {
		if (p->getId() == purchaseId) {
			if (p->deliver()) { // Вече е указател, променяме го директно!
				std::cout << "Purchase delivered.\n";
			} else {
				std::cout << "Not PENDING.\n";
			}
			return;
		}
	}
	std::cout << "Purchase not found.\n";
}

void NotinOOP::removeReview(unsigned int fragId, unsigned int reviewId) {
    if (!getLoggedInAdmin()) { std::cout << "Admin privileges required!\n"; return; }
    for (auto& f : catalog) {
        if (f.getId() == fragId) {
            if (f.removeReview(reviewId)) std::cout << "Review removed.\n";
            else std::cout << "Review not found.\n";
            return;
        }
    }
    std::cout << "Fragrance not found.\n";
}

//Файлова система
void NotinOOP::saveDatabase() {
	std::cout << "Saving database...\n";

	//1. Запазваме потребителите (users.txt)
	std::ofstream userFile("users.txt");
	if (userFile.is_open()) {
		for (const auto& u : users) {
			//Проверяваме какъв тип е потребителят, за да запазим правилните данни
			if (Customer* c = dynamic_cast<Customer*>(u.get())) {
				//Формат: C [id] [username] [password] [balance]
				userFile << "C " << c->getId() << " " << c->getUsername() << " "
						 << c->getPassword() << " " << c->getBalance() << "\n";
			}
			else if (Admin* a = dynamic_cast<Admin*>(u.get())) {
				//Формат: A [id] [username] [password]
				userFile << "A " << a->getId() << " " << a->getUsername() << " "
						 << a->getPassword() << "\n";
			}
		}
		userFile.close();
	} else {
		std::cout << "Error: Could not open users.txt for writing.\n";
	}

	//2. Запазваме каталога (catalog.txt)
	std::ofstream catFile("catalog.txt");
	if (catFile.is_open()) {
		for (const auto& f : catalog) {
			//Формат: [id] [name] [brand_int] [price] [family_int] [quantity]
			catFile << f.getId() << " " << f.getName() << " "
					<< static_cast<int>(f.getBrand()) << " "
					<< f.getPrice() << " "
					<< static_cast<int>(f.getFamily()) << " "
					<< f.getQuantity() << "\n";
		}
		catFile.close();
	} else {
		std::cout << "Error: Could not open catalog.txt for writing.\n";
	}

	std::cout << "Database saved successfully!\n";
}

void NotinOOP::loadDatabase() {
	//1. Зареждаме потребителите (users.txt)
	std::ifstream userFile("users.txt");
	if (userFile.is_open()) {
		users.clear();
		//Изтриваме дефолтния админ, за да заредим тези от файла

		std::string type, name, pass;
		unsigned int id;
		double balance;

		while (userFile >> type) {
			if (type == "C") {
				userFile >> id >> name >> pass >> balance;
				auto newCustomer = std::make_unique<Customer>(id, name, pass);
				newCustomer->addToBalance(balance);
				//Възстановяваме парите
				users.push_back(std::move(newCustomer));
			}
			else if (type == "A") {
				userFile >> id >> name >> pass;
				users.push_back(std::make_unique<Admin>(id, name, pass));
			}
		}
		userFile.close();
	}

	//Ако след опита за четене нямаме никакви потребители (напр. при първо пускане на нова програма), създаваме дефолтния админ, за да не се заключим извън системата.
	if (users.empty()) {
		users.push_back(std::make_unique<Admin>(0, "admin", "admin123"));
	}

	//2. Зареждаме каталога (catalog.txt)
	std::ifstream catFile("catalog.txt");
	if (catFile.is_open()) {
		catalog.clear();

		unsigned int id, q;
		std::string name;
		int brandInt, familyInt;
		double price;

		while (catFile >> id >> name >> brandInt >> price >> familyInt >> q) {
			Fragrance f(id, name, static_cast<Brand>(brandInt), price, static_cast<FragranceFamily>(familyInt), q);
			catalog.push_back(f);
		}
		catFile.close();
	}
}
//Раздели файлове функции