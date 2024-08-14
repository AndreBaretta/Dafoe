// Includes
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include "../DafoeGod/DafoeGod.hpp"

// Main Process
int main()
{
   DafoeGod Atlas{};
   Atlas.query("insert into product (id, name, quantity, category) value (2, 'pedro', 10, 0)");
   Atlas.query("insert into product (id, name, quantity, category) value (3, 'joao', 10, 0)");

   return 0;
}
