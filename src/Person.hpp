

class Pessoa : public Cliente{
   public:
      Pessoa(){}
      ~Pessoa(){}
      
      // Setters
      bool setCpf(std::string);

      // Getters
      std::string getCpf();

   private:
      std::string cpf{};
}