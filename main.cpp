#include <iostream>
#include <pqxx/pqxx>

class TablesClient
{
	pqxx::connection* conn;
public:
	
	void Connect() {
		{
			try {
				conn = new pqxx::connection("host = 127.0.0.1 "
					"port=5432 "
					"dbname=CPPbd "
					"user=postgres "
					"password=7845");
				std::cout << "Connection OK!" << std::endl;

			}
			catch (const std::exception& e)
			{
				std::cout << "Connection error!" << e.what() << std::endl;
			}
		}
	}
	
	void CreateTables()
	{
		pqxx::transaction t(*conn);

		t.exec("create table IF NOT EXISTS Client ( "
			"id serial primary key, "
			"name VARCHAR not null, "
			"lastname VARCHAR not null, "
			"email VARCHAR not null );");
			
		t.commit();
	}

	void Phone()
	{
		
		pqxx::transaction phones(*conn);
		phones.exec("create table IF NOT EXISTS Phone ( "
			"id serial primary key, "
			"phone bigint, "
			"id_phone bigint references Client(id)); ");

		phones.commit();
	}

	void AddClient(std::string name, std::string lastname, std::string email)
	{
		
		pqxx::transaction ac(*conn);
		ac.exec("INSERT INTO Client(id, name, lastname, email) values (1, '" + name + "', '" + lastname + "', '" + email + "')");
		ac.commit();
	}

	void AddPhone(std::string phone)
	{
		pqxx::transaction ap(*conn);
		ap.exec("INSERT INTO Phone(id,phone,id_phone) values (1, '" + phone + "' , 1)");
		ap.commit();
	}

	void UpdateClient(std::string updname)
	{
		pqxx::transaction uc(*conn);
		uc.exec("UPDATE Client set name='" + updname+ "' where id =1");
		uc.commit();
	}

	void DeletePhone()
	{
		pqxx::transaction dp(*conn);
		dp.exec("DELETE from Phone where id=1");
		dp.exec("DELETE from Phone where id=2");
		dp.commit();
	}

	void DeleteClient()
	{
		pqxx::transaction dc(*conn);
		dc.exec("DELETE from Client where id=1");
		dc.commit();
	}

	void SearchClient()
	{
		pqxx::transaction t(*conn);
		auto result = t.exec("SELECT * FROM Client where name = 'ANDREY'");
		t.commit();
	}
};

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");

	try {
		TablesClient tb;
		tb.Connect();
		tb.CreateTables();
		tb.AddClient("Andrey", "Lavrentev", "LavAnd@mail.ru");
		tb.Phone();
		tb.AddPhone("88005553535");
		tb.UpdateClient("ANDREY");
		tb.SearchClient();
		tb.DeletePhone();
		tb.DeleteClient();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception happened!" << e.what() << std::endl;
	}
}
