#include <iostream>
#include <string>
#include <vector>
#include <pqxx/pqxx>

using namespace std;

// Структура для хранения данных о клиенте
struct ClientData {
    int id;
    string first_name;
    string last_name;
    string email;
    vector<string> phones;
};

class ClientDB {
public:
    // Конструктор
    ClientDB(const string& conn_str) : conn_(conn_str) {}
    
    // 1. Создание структуры БД
    void create_schema() {
        pqxx::work tx{ conn_ };
        tx.exec(
            "CREATE TABLE IF NOT EXISTS clients("
            "id SERIAL PRIMARY KEY,"
            "first_name VARCHAR(50) NOT NULL,"
            "last_name VARCHAR(50) NOT NULL,"
            "email VARCHAR(100) UNIQUE NOT NULL"
            ");"
        );
        tx.exec(
            "CREATE TABLE IF NOT EXISTS phones("
            "id SERIAL PRIMARY KEY,"
            "client_id INTEGER NOT NULL REFERENCES clients(id) ON DELETE CASCADE,"
            "phone VARCHAR(30) NOT NULL"
            ");"
        );
        tx.commit();
    }

    // 2. Добавить нового клиента, возвращает id
    int add_client(const string& first, const string& last, const string& email) {
        pqxx::work tx{ conn_ };
        // Исправлено: INTERT -> INSERT
        pqxx::result r = tx.exec_params(
            "INSERT INTO clients(first_name, last_name, email) "
            "VALUES ($1, $2, $3) RETURNING id;",
            first, last, email);
        int id = r[0][0].as<int>();
        tx.commit();
        return id;
    }

    // 3. Добавить телефон существующему клиенту
    void add_phone(int client_id, const string& phone) {
        pqxx::work tx{ conn_ };
        tx.exec_params(
            "INSERT INTO phones(client_id, phone) VALUES ($1, $2);",
            client_id, phone
        );
        tx.commit();
    }

    // 4. Изменить данные о клиенте 
    void update_client(int client_id,
        const string& new_first,
        const string& new_last,
        const string& new_email)
    {
        pqxx::work tx{ conn_ };

        if (!new_first.empty()) {
            tx.exec_params(
                "UPDATE clients SET first_name = $1 WHERE id = $2;",
                new_first, client_id
            );
        }
        if (!new_last.empty()) {
            tx.exec_params(
                "UPDATE clients SET last_name = $1 WHERE id = $2;",
                new_last, client_id
            );
        }
        if (!new_email.empty()) {
            tx.exec_params(
                "UPDATE clients SET email = $1 WHERE id = $2;",
                new_email, client_id
            );
        }
        tx.commit();
    }

    // 5. Удалить телефон у клиента
    void delete_phone(int client_id, const string& phone) {
        pqxx::work tx{ conn_ };
        tx.exec_params(
            "DELETE FROM phones WHERE client_id = $1 AND phone = $2;",
            client_id, phone
        );
        tx.commit();
    }

    // 6. Удалить клиента (телефоны удаляются каскадно)
    void delete_client(int client_id) {
        pqxx::work tx{ conn_ };
        tx.exec_params("DELETE FROM clients WHERE id = $1;", client_id);
        tx.commit();
    }

    // 7. Поиск клиента по имени / фамилии / email / телефону
    // Возвращает вектор найденных клиентов
    vector<ClientData> find_client(const string& first,
                                   const string& last,
                                   const string& email,
                                   const string& phone)
    {
        vector<ClientData> result;
        
        // Первый запрос: находим ID клиентов по критериям
        pqxx::work tx{ conn_ };

        string sql =
            "SELECT DISTINCT c.id "
            "FROM clients c "
            "LEFT JOIN phones p ON c.id = p.client_id "
            "WHERE 1=1 ";

        if (!first.empty()) sql += "AND c.first_name = " + tx.quote(first) + " ";
        if (!last.empty())  sql += "AND c.last_name  = " + tx.quote(last) + " ";
        if (!email.empty()) sql += "AND c.email      = " + tx.quote(email) + " ";
        if (!phone.empty()) sql += "AND p.phone      = " + tx.quote(phone) + " ";

        pqxx::result client_ids = tx.exec(sql);
        
        // Для каждого найденного клиента получаем полные данные
        for (const auto& row : client_ids) {
            int client_id = row["id"].as<int>();
            
            // Получаем основные данные клиента
            pqxx::result client_info = tx.exec_params(
                "SELECT first_name, last_name, email FROM clients WHERE id = $1",
                client_id
            );
            
            ClientData client;
            client.id = client_id;
            client.first_name = client_info[0]["first_name"].as<string>();
            client.last_name = client_info[0]["last_name"].as<string>();
            client.email = client_info[0]["email"].as<string>();
            
            // Получаем телефоны клиента
            pqxx::result phone_info = tx.exec_params(
                "SELECT phone FROM phones WHERE client_id = $1",
                client_id
            );
            
            for (const auto& phone_row : phone_info) {
                client.phones.push_back(phone_row["phone"].as<string>());
            }
            
            result.push_back(client);
        }
        
        tx.commit();
        return result;
    }

private:
    pqxx::connection conn_;
};

// Вспомогательная функция для вывода данных клиента
void print_client(const ClientData& client) {
    cout << "id=" << client.id
         << " " << client.first_name
         << " " << client.last_name
         << " email=" << client.email
         << " phones: ";
    
    if (client.phones.empty()) {
        cout << "(none)";
    } else {
        for (size_t i = 0; i < client.phones.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << client.phones[i];
        }
    }
    cout << endl;
}

int main() {
    try {
        // строка подключения под себя
        ClientDB db("host=localhost port=5432 dbname=clients_db user=postgres password=postgres");

        db.create_schema();

        int id1 = db.add_client("Ivan", "Ivanov", "ivan@example.com");
        int id2 = db.add_client("Petr", "Petrov", "petr@example.com");
        int id3 = db.add_client("Anna", "Smirnova", "anna@example.com");

        db.add_phone(id1, "+7-900-111-22-33");
        db.add_phone(id1, "+7-900-111-22-44");
        db.add_phone(id2, "+7-900-222-33-44");

        db.update_client(id3, "", "", "anna.smirnova@example.com");

        cout << "Поиск по email:\n";
        vector<ClientData> found = db.find_client("", "", "ivan@example.com", "");
        for (const auto& client : found) {
            print_client(client);
        }

        cout << "\nПоиск по телефону:\n";
        found = db.find_client("", "", "", "+7-900-222-33-44");
        for (const auto& client : found) {
            print_client(client);
        }

        // пример удаления телефона и клиента
        db.delete_phone(id1, "+7-900-111-22-44");
        db.delete_client(id2);

        cout << "\nПосле удаления:\n";
        found = db.find_client("", "", "", "");
        for (const auto& client : found) {
            print_client(client);
        }
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }

    return 0;
}
