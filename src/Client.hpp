

class Cliente{
   public:
      Cliente(){}
      ~Cliente{}

      // Setters
      bool setId(int);
      bool setName(std::string);
      bool setAddress(std::string);
      bool setBill(double);
      
      // Getters
      int getId();
      std::string getName();
      std::string getAddress();
      double getBill();

   private:
      int id{};
      std::string name{};
      std::string address{};
      double bill{};
}

