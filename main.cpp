#include <iostream>
#include <pqxx/pqxx>

class TablesClient
{
public:

	void CreateTables(pqxx::connection& conn)
	{
		pqxx::transaction t(conn);

		t.exec("create table IF NOT EXISTS Client ( "
			"id serial primary key, "
			"name VARCHAR not null, "
			"lastname VARCHAR not null, "
			"email VARCHAR not null );"); 
			
		t.commit();
	}

	void Phone(pqxx::connection& conn)
	{
		pqxx::transaction phones(conn);
		phones.exec("create table IF NOT EXISTS Phone ( "
			"id serial primary key, "
			"phone bigint, "
			"id_phone bigint references Client(id)); ");

		phones.commit();
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	try {

		pqxx::connection conn("host=127.0.0.1 "
			"port=5432 "
			"dbname=CPPbd "
			"user=postgres "
			"password=7845");

		TablesClient tb;
		tb.CreateTables(conn);
		tb.Phone(conn);

		pqxx::transaction t(conn);

		t.exec("INSERT INTO Client(id, name, lastname, email) values (1, 'Andrey', 'Lavrentev', 'AndLav@mail.ru')");
		

		t.exec("INSERT INTO Phone(id,phone,id_phone) values (1, 88005553535, 1)");
		

		t.exec("INSERT INTO Phone (id,phone,id_phone) values (2, 8999999999, 1 )");
		
		t.exec("UPDATE Client set name='ANDREY' where id = 1");

		auto result = t.exec("SELECT * FROM Client where name = 'ANDREY'");
		
		for (auto& a : result)
		{
			
		}

		t.exec("DELETE from Phone where id=1");
		t.exec("DELETE from Phone where id=2");
		t.exec("DELETE from Client where id=1");

		t.commit();
		std::cout << "OK!" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception happened!" << e.what() << std::endl;
	}
}