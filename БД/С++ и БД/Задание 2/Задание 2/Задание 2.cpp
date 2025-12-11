#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

namespace dbo = Wt::Dbo;

class Publisher;
class Book;
class Shop;
class Stock;
class Sale;

class Publisher {
public:
    string name = "";

    dbo::collection<dbo::ptr<Book>> books;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::hasMany(a, books, dbo::ManyToOne, "publisher");
    }
};

class Book {
public:
    string title = "";

    dbo::ptr<Publisher> publisher;
    dbo::collection<dbo::ptr<Stock>> stocks;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, title, "title");
        dbo::belongsTo(a, publisher, "publisher");
        dbo::hasMany(a, stocks, dbo::ManyToOne, "book");
    }
};

class Shop {
public:
    string name = "";

    dbo::collection<dbo::ptr<Stock>> stocks;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::hasMany(a, stocks, dbo::ManyToOne, "shop");
    }
};

class Stock {
public:
    int count = 0;

    dbo::ptr<Book> book;
    dbo::ptr<Shop> shop;
    dbo::collection<dbo::ptr<Sale>> sales;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, count, "count");
        dbo::belongsTo(a, book, "book");
        dbo::belongsTo(a, shop, "shop");
        dbo::hasMany(a, sales, dbo::ManyToOne, "stock");
    }
};

class Sale {
public:
    double price = 0.0;
    string date_sale = "";
    int count = 0;

    dbo::ptr<Stock> stock;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, price, "price");
        dbo::field(a, date_sale, "date_sale");
        dbo::field(a, count, "count");
        dbo::belongsTo(a, stock, "stock");
    }
};

void fillTestData(dbo::Session& session) {
    dbo::Transaction transaction{ session };

    try {
        auto publisher1 = session.add(make_unique<Publisher>());
        publisher1.modify()->name = "Penguin Books";

        auto publisher2 = session.add(make_unique<Publisher>());
        publisher2.modify()->name = "HarperCollins";

        auto book1 = session.add(make_unique<Book>());
        book1.modify()->title = "1984";
        book1.modify()->publisher = publisher1;

        auto book2 = session.add(make_unique<Book>());
        book2.modify()->title = "Animal Farm";
        book2.modify()->publisher = publisher1;

        auto book3 = session.add(make_unique<Book>());
        book3.modify()->title = "The Hobbit";
        book3.modify()->publisher = publisher2;

        auto shop1 = session.add(make_unique<Shop>());
        shop1.modify()->name = "Bookstore Central";

        auto shop2 = session.add(make_unique<Shop>());
        shop2.modify()->name = "Literary Haven";

        auto shop3 = session.add(make_unique<Shop>());
        shop3.modify()->name = "Reading Corner";

        auto stock1 = session.add(make_unique<Stock>());
        stock1.modify()->book = book1;
        stock1.modify()->shop = shop1;
        stock1.modify()->count = 10;

        auto stock2 = session.add(make_unique<Stock>());
        stock2.modify()->book = book2;
        stock2.modify()->shop = shop1;
        stock2.modify()->count = 5;

        auto stock3 = session.add(make_unique<Stock>());
        stock3.modify()->book = book1;
        stock3.modify()->shop = shop2;
        stock3.modify()->count = 8;

        auto stock4 = session.add(make_unique<Stock>());
        stock4.modify()->book = book3;
        stock4.modify()->shop = shop3;
        stock4.modify()->count = 12;

        auto sale1 = session.add(make_unique<Sale>());
        sale1.modify()->stock = stock1;
        sale1.modify()->price = 12.99;
        sale1.modify()->date_sale = "2024-01-15";
        sale1.modify()->count = 2;

        auto sale2 = session.add(make_unique<Sale>());
        sale2.modify()->stock = stock3;
        sale2.modify()->price = 11.99;
        sale2.modify()->date_sale = "2024-01-16";
        sale2.modify()->count = 1;

        transaction.commit();
        cout << "Test data created successfully!" << endl;
    }
    catch (const dbo::Exception& e) {
        cerr << "Error creating test data: " << e.what() << endl;
        throw;
    }
}

int main() {
    try {
        string connectionString =
            "host=localhost "
            "port=5432 "
            "dbname=bookstore_db "
            "user=postgres "
            "password=your_password "
            "client_encoding=UTF8";

        auto postgres = make_unique<dbo::backend::Postgres>(connectionString);

        dbo::Session session;
        session.setConnection(move(postgres));

        session.mapClass<Publisher>("publisher");
        session.mapClass<Book>("book");
        session.mapClass<Shop>("shop");
        session.mapClass<Stock>("stock");
        session.mapClass<Sale>("sale");

        try {
            session.createTables();
            cout << "Tables created successfully!" << endl;
        }
        catch (const dbo::Exception& e) {
            cout << "Tables might already exist: " << e.what() << endl;
        }

        fillTestData(session);

        cout << "\nEnter publisher name or ID (or 'list' to see all publishers): ";
        string input;
        getline(cin, input);

        dbo::Transaction transaction{ session };

        if (input == "list") {
            
            auto publishers = session.find<Publisher>();
            cout << "\nAvailable publishers:" << endl;
            for (const dbo::ptr<Publisher>& pub : publishers) {
                cout << "ID: " << pub.id() << ", Name: " << pub->name << endl;
            }

            cout << "\nEnter publisher name or ID: ";
            getline(cin, input);
        }

        dbo::ptr<Publisher> publisher;

        try {
            long long id = stoll(input);
            publisher = session.find<Publisher>().where("id = ?").bind(id);
        }
        catch (...) {
            publisher = session.find<Publisher>().where("name = ?").bind(input);
        }

        if (publisher) {
            scout << "\nPublisher found: " << publisher->name << endl;

            vector<string> shopNames;

            auto books = publisher->books;

            cout << "\nBooks by this publisher:" << endl;
            for (const dbo::ptr<Book>& book : books) {
               cout << " - " << book->title << endl;

                auto stocks = book->stocks;

                for (const dbo::ptr<Stock>& stock : stocks) {
                    if (stock->shop && stock->count > 0) {
                        shopNames.push_back(stock->shop->name);
                    }
                }
            }

            sort(shopNames.begin(), shopNames.end());
            shopNames.erase(unique(shopNames.begin(), shopNames.end()), shopNames.end());

            if (!shopNames.empty()) {
                cout << "\nShops selling books from this publisher:" << endl;
                for (const auto& shopName : shopNames) {
                    cout << " - " << shopName << endl;
                }
            }
            else {
                cout << "\nNo shops found selling books from this publisher." << endl;
            }
        }
        else {
            cout << "\nPublisher not found!" << endl;
        }

        transaction.commit();

    }
    catch (const dbo::Exception& e) {
        cerr << "Database error: " << e.what() << endl;
        return 1;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}