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
				std::cout << "OK!" << std::endl;

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

	void AddClient()
	{
		
		pqxx::transaction ac(*conn);
		ac.exec("INSERT INTO Client(id, name, lastname, email) values (1, 'Andrey', 'Lavrentev', 'AndLav@mail.ru')");
		ac.commit();
	}

	void AddPhone()
	{
		pqxx::transaction ap(*conn);
		ap.exec("INSERT INTO Phone(id,phone,id_phone) values (1, 88005553535, 1)");
		ap.exec("INSERT INTO Phone (id,phone,id_phone) values (2, 8999999999, 1 )");
		ap.commit();
	}

	void UpdateClient()
	{
		pqxx::transaction uc(*conn);
		uc.exec("UPDATE Client set name='ANDREY' where id = 1");
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
	setlocale(LC_ALL, "Russian");
	try {
		TablesClient tb;
		tb.Connect();
		tb.CreateTables();
		tb.AddClient();
		tb.Phone();
		tb.UpdateClient();
		tb.SearchClient();
		tb.DeletePhone();
		tb.DeleteClient();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception happened!" << e.what() << std::endl;
	}
}
