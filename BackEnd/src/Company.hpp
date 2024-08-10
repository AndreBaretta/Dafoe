

class Empresa : public Cliente{
   public:
      Empresa(){}
      ~Empresa(){}

      // Setters
      bool setCnpj(std::string);

      // Getters
      std::string getCnpj();

   private:
      std::string cnpj{};
}

