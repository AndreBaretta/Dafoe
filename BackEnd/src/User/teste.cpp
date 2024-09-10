#include "UserDAO.hpp"
#include "UserMNG.hpp"
#include "../DafoeGod/DafoeGod.hpp"

int main(){
    DafoeGod dafoe{};
    UserDAO user{dafoe};

    user.createUser(1, "carlos", "123", true);
}
