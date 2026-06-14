#include "Purchase.h"

Purchase::Purchase(unsigned int pId, unsigned int uId, const std::vector<Fragrance>& items, double price)
    : purchaseId(pId), userId(uId), fragrances(items), state(OrderState::PENDING), finalPrice(price) {
}

//Get-ъри
unsigned int Purchase::getId() const { return purchaseId; }
unsigned int Purchase::getUserId() const { return userId; }
OrderState Purchase::getState() const { return state; }
double Purchase::getFinalPrice() const { return finalPrice; }
const std::vector<Fragrance>& Purchase::getFragrances() const { return fragrances; }

//Смяна на състоянието към DELIVERED
bool Purchase::deliver() {
    //Поръчка може да бъде доставена само ако все още е PENDING
    if (state == OrderState::PENDING) {
        state = OrderState::DELIVERED;
        return true;
    }
    return false;
}

bool Purchase::cancel() {
    //Поръчка може да бъде отказана само ако е PENDING
    if (state == OrderState::PENDING) {
        state = OrderState::CANCELED;
        return true;
    }
    return false;
}

//Помощна функция за принтиране на състоянието
std::string Purchase::stateToString() const {
    switch (state) {
        case OrderState::PENDING: return "PENDING";
        case OrderState::DELIVERED: return "DELIVERED";
        case OrderState::CANCELED: return "CANCELED";
        default: return "UNKNOWN";
    }
}

//Показване на информацията за поръчката
void Purchase::show() const {
    std::cout << "====================================\n"
              << "Purchase ID: #" << purchaseId << "\n"
              << "Buyer ID: " << userId << "\n"
              << "State: " << stateToString() << "\n"
              << "Total Price Paid: $" << finalPrice << "\n"
              << "--- Items in this purchase ---\n";

    for (const Fragrance& f : fragrances) {
        //Принтваме само основна информация за парфюмите в поръчката
        std::cout << " - " << f.getName() << " (" << brandToString(f.getBrand()) << ")\n";
    }
    std::cout << "====================================\n";
}