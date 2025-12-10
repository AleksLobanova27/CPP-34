#include <iostream>
#include <string>
#include <vector>
#include <pqxx/pqxx>
using namespace std;

class ClientDB(const string& conn_str) :conn_(conn_str) {
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
		pqxx::result r = tx.exec_params(
			"INTERT INTO clients(first_name, last_name, email)"
			"VALUES ($1, $2, $3) RETURNING id;",
			first, last, email);
		int id = r[0][0].as<int>();
		tx.commit();
		return id;
	}

	// 3. Добавить телефон существующему клиенту
	void add_phone(int client_id < const string& phone) {
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

    // 6. Удалить клиента (телефоны удалятся каскадно)
    void delete_client(int client_id) {
        pqxx::work tx{ conn_ };
        tx.exec_params("DELETE FROM clients WHERE id = $1;", client_id);
        tx.commit();
    }

    // 7. Поиск клиента по имени / фамилии / email / телефону

    void find_client(const string& first,
        const string& last,
        const string& email,
        const string& phone)
    {
        pqxx::work tx{ conn_ };

        string sql =
            "SELECT c.id, c.first_name, c.last_name, c.email, p.phone "
            "FROM clients c "
            "LEFT JOIN phones p ON c.id = p.client_id "
            "WHERE 1=1 ";

        if (!first.empty()) sql += "AND c.first_name = " + tx.quote(first) + " ";
        if (!last.empty())  sql += "AND c.last_name  = " + tx.quote(last) + " ";
        if (!email.empty()) sql += "AND c.email      = " + tx.quote(email) + " ";
        if (!phone.empty()) sql += "AND p.phone      = " + tx.quote(phone) + " ";

        pqxx::result r = tx.exec(sql);

        for (const auto& row : r) {
            cout << "id=" << row["id"].as<int>()
                << " " << row["first_name"].c_str()
                << " " << row["last_name"].c_str()
                << " email=" << row["email"].c_str()
                << " phone=";
            if (row["phone"].is_null())
                cout << "(none)";
            else
                cout << row["phone"].c_str();
            cout << endl;
        }
        
    }

private:
    pqxx::connection conn_;
};

iint main() {
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
        db.find_client("", "", "ivan@example.com", "");

        cout << "Поиск по телефону:\n";
        db.find_client("", "", "", "+7-900-222-33-44");

        // пример удаления телефона и клиента
        db.delete_phone(id1, "+7-900-111-22-44");
        db.delete_client(id2);

        cout << "После удаления:\n";
        db.find_client("", "", "", "");
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }

    return 0;
}
