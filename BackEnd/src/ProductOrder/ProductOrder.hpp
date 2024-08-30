#ifndef PRODUCTORDER_2332
#define PRODUCTORDER_2332

class ProductOrder {
public:
    ProductOrder(int sellOrder, int product, int quantity, double discount, double price);

    // Setters
    bool setSellOrder(int sellOrder);
    bool setProduct(int product);
    bool setQuantity(int quantity);
    bool setDiscount(double discount);
    bool setPrice(double price);

    // Getters
    int getSellOrder() const;
    int getProduct() const;
    int getQuantity() const;
    double getDiscount() const;
    double getPrice() const;

private:
    int m_SellOrder{};
    int m_product{};
    int m_quantity{};
    double m_discount{};
    double m_price{};
};

#endif

