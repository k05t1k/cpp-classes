#include <iostream>
#include <vector>
#include <string>
#include <map>

class Sneaker {
public:
    std::string name;
    std::string countryCode;
    std::vector<int> sizes;
    double price;
    int quantity;

    Sneaker(std::string name, std::string countryCode, std::vector<int> sizes, double price, int quantity) {
        this->name = name;
        this->countryCode = countryCode;
        this->sizes = sizes;
        this->price = price;
        this->quantity = quantity;
    }
};

class Store {
public:
    std::vector<Sneaker> sneakers;

    void addSneaker(Sneaker sneaker) {
        sneakers.push_back(sneaker);
    }

    void updateSneaker(int index, Sneaker updatedSneaker) {
        if (index >= 0 && index < sneakers.size()) {
            sneakers[index] = updatedSneaker;
        } else {
            std::cout << "Неправильный индекс." << std::endl;
        }
    }

    void deleteSneaker(int index) {
        if (index >= 0 && index < sneakers.size()) {
            sneakers.erase(sneakers.begin() + index);
        } else {
            std::cout << "Неправильный индекс." << std::endl;
        }
    }

    Sneaker getSneaker(int index) {
        if (index >= 0 && index < sneakers.size()) {
            return sneakers[index];
        } else {
            std::cout << "Неправильный индекс." << std::endl;
            return Sneaker("", "", {}, 0, 0);
        }
    }

    std::vector<Sneaker> getAllSneakers() {
        return sneakers;
    }
};

class Cart {
private:
    std::map<int, int> items;
    Store &store;

public:
    Cart(Store &store) : store(store) {}

    void addItem(int sneakerIndex, int quantity) {
        Sneaker sneaker = store.getSneaker(sneakerIndex);

        if (sneaker.name != "" && sneaker.quantity >= quantity) {
            items[sneakerIndex] += quantity;
            store.sneakers[sneakerIndex].quantity -= quantity;
        } else {
            std::cout << "Кроссовки недоступны, или недостаточно количества." << std::endl;
        }
    }

    void removeItem(int sneakerIndex) {
        if (items.find(sneakerIndex) != items.end()) {
            int quantity = items[sneakerIndex];
            items.erase(sneakerIndex);
            store.sneakers[sneakerIndex].quantity += quantity;
        } else {
            std::cout << "Предмета нет в корзине." << std::endl;
        }
    }

    double getTotal() {
        double total = 0;

        for (auto const &item : items) {
            Sneaker sneaker = store.getSneaker(item.first);
            total += sneaker.price * item.second;
        }

        return total;
    }

    void printReceipt() {
        std::cout << "--- Чек ---" << std::endl;

        for (auto const &item : items) {
            Sneaker sneaker = store.getSneaker(item.first);
            std::cout << sneaker.name << " x" << item.second << " - $" << sneaker.price * item.second << std::endl;
        }

        std::cout << "Цена: $" << getTotal() << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    Store store;
    Cart cart(store);

    store.addSneaker(Sneaker("Nike Air", "US", {40, 41, 42}, 100, 5));
    store.addSneaker(Sneaker("Adidas Ultra", "DE", {41, 43, 44}, 120, 3));

    cart.addItem(0, 2);
    cart.addItem(1, 1);

    cart.printReceipt();

    return 0;
}
