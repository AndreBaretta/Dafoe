#ifndef SESSION_1534
#define SESSION_1534

class Session{
public:
   Session(const int id, const bool isAdmin);
   int getId();
   bool getAdmin();
private:
   int m_id{};
   bool m_admin{};
};

#endif

