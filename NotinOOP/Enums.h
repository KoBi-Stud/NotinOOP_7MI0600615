#pragma once
#include <string>

//Състояния на поръчката
enum class OrderState {
	PENDING,
	DELIVERED,
	CANCELED
};

//Списък с марки (Brand)
enum class Brand {
	CHANEL,
	DIOR,
	TOM_FORD,
	ARMANI,
	VERSACE,
	UNKNOWN //Имаме default/unknown стойност
};

//Нотки на парфюмите (Fragrance Family)
enum class FragranceFamily {
	FLORAL,
	WOODY,
	CITRUS,
	ORIENTAL,
	FRESH,
	UNKNOWN
};

// Помощна функция за превръщане на Enum в String (за принтване и запазване във файл)
inline std::string brandToString(Brand b) {
	switch (b) {
		case Brand::CHANEL: return "Chanel";
		case Brand::DIOR: return "Dior";
		case Brand::TOM_FORD: return "Tom Ford";
		case Brand::ARMANI: return "Armani";
		case Brand::VERSACE: return "Versace";
		default: return "Unknown";
	}
}