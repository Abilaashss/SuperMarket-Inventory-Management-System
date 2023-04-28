#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <algorithm>
#include <ctime>
using namespace std;

class Product
{
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;

public:
    Product(int id, string name, string category, double price, int quantity)
    {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = price;
        this->quantity = quantity;
    }

    int getId() const
    {
        return id;
    }

    void setId(int id)
    {
        this->id = id;
    }

    string getName() const
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    string getCategory() const
    {
        return category;
    }

    void setCategory(string category)
    {
        this->category = category;
    }

    double getPrice() const
    {
        return price;
    }

    void setPrice(double price)
    {
        this->price = price;
    }

    int getQuantity() const
    {
        return quantity;
    }

    void setQuantity(int quantity)
    {
        this->quantity = quantity;
    }
};

class Inventory
{
private:
    vector<Product> products;
    vector<string> wishlist; // Add wishlist vector
public:

    void addProduct(Product product)
    {
        bool found = false;
        for (auto &p : products)
        {
            if (p.getId() == product.getId())
            {
                cout << "Id already Exist." << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            products.push_back(product);
            cout << "Product added successfully." << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }

    vector<Product> &getProducts()
    {
        return products;
    }

    void removeProduct(int id)
    {
        bool found = false;
        for (auto i = products.begin(); i != products.end(); i++)
        {
            if (i->getId() == id)
            {
                products.erase(i);
                found = true;
                cout << "Product removed successfully." << endl;
                cout << "-----------------------------------------------------------" << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Id does not exist" << endl;
        }
    }

    Product *findProduct(int id)
    {
        for (auto i = products.begin(); i != products.end(); i++)
        {
                       if (i->getId() == id)
            {
                return &(*i);
            }
        }
        return nullptr;
    }


string getCurrentDate() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}

	void addToWishlist(const string& product)
    {
        wishlist.push_back(product);
        cout << "Product added to the wishlist." << endl;
    }

    void viewWishlist() const
    {
        if (wishlist.empty())
        {
            cout << "Wishlist is empty." << endl;
        }
        else
        {
            cout << "Wishlist:" << endl;
            for (const auto& product : wishlist)
            {
                cout << product << endl;
            }
        }
    }
    void saveInventoryToFile(string filename) 
    {
        ofstream file;
        file.open(filename, ios::out | ios::trunc); // Truncate the file before writing new data

        if (file.is_open()) 
        {
            for (const auto& product : products) 
            {
                file << product.getId() << ","
                     << product.getName() << ","
                     << product.getCategory() << ","
                     << product.getPrice() << ","
                     << product.getQuantity() << endl;
            }

            file.close();
        } 
        else 
        {
            cout << "Error: Could not open file " << filename << endl;
        }
    }

        void loadInventoryFromFile(string filename) 
        {
            ifstream file;
            file.open(filename);

            if (file.is_open()) 
            {
                string line;
                while (getline(file, line)) 
                {
                    stringstream ss(line);
                    string idStr, name, category, priceStr, quantityStr;
                    getline(ss, idStr, ',');
                    getline(ss, name, ',');
                    getline(ss, category, ',');
                    getline(ss, priceStr, ',');
                    getline(ss, quantityStr, ',');

                    int id = stoi(idStr);
                    double price = stod(priceStr);
                    int quantity = stoi(quantityStr);

                    Product p(id, name, category, price, quantity);
                    products.push_back(p);
                }

                file.close();
            } else {
                cout << "Error: Could not open file " << filename << endl;
            }	
        }
        void saveWishlistToFile(const string& filename) const
    {
        ofstream file(filename);

        if (file.is_open())
        {
            for (const auto& product : wishlist)
            {
                file << product << endl;
            }

            file.close();
            cout << "Saving..........." << endl;
        }
        else
        {
            cout << "Error: Could not open file " << filename << endl;
        }
    }

    void loadWishlistFromFile(const string& filename)
    {
        ifstream file(filename);

        if (file.is_open())
        {
            string product;
            while (getline(file, product))
            {
                wishlist.push_back(product);
            }

            file.close();
        }
        else
        {
            cout << "Error: Could not open file " << filename << endl;
        }
    }
    void returnProduct()
{
    int id, quantity;
    char choice;

    do {
        cout << "Enter the ID of the product you want to return: ";
        cin >> id;

        Product *product = findProduct(id);
        if (product == nullptr)
        {
            cout << "Product with ID " << id << " does not exist." << endl;
            continue;
        }

        cout << "Product found: " << product->getName() << " (ID: " << product->getId() << ")" << endl;

        cout << "Enter the quantity you want to return: ";
        cin >> quantity;

        product->setQuantity(product->getQuantity() + quantity);
        cout << "Product returned successfully!" << endl;

        cout << "Do you want to return anything else? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');
}

     void displayProducts();
     void updateProduct();
     void buyProduct();
    void generateBill();
};
void Inventory::displayProducts() {
    int choice;
    cout << "---------------- Display Options ----------------" << endl;
    cout << "1. Display by ID" << endl;
    cout << "2. Display by Category" << endl;
    cout << "3. Display All" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    cout << "-----------------------------------------------------------" << endl;

    switch (choice) {
        case 1: {
            int id;
            cout << "Enter the ID of the product: ";
            cin >> id;
            cout << endl;

            Product *product = findProduct(id);
            if (product != nullptr) {
                cout << "Product Found:" << endl;
                cout << "ID: " << product->getId() << endl;
                cout << "Name: " << product->getName() << endl;
                cout << "Category: " << product->getCategory() << endl;
                cout << "Price: $" << product->getPrice() << endl;
                cout << "Quantity: " << product->getQuantity() << endl;
                cout << "-----------------------------------------------------------" << endl;
            } else {
                cout << "Product with ID " << id << " does not exist." << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            break;
        }
        
        case 2:
        {
            // Display by Category
            cout << "Available Categories:" << endl;

            // Collect all unique categories
            set<string> uniqueCategories;
            for (const auto &product : products)
            {
                uniqueCategories.insert(product.getCategory());
            }

            // Display categories with indices
            int index = 1;
            for (const auto &category : uniqueCategories)
            {
                cout << index++ << ". " << category << endl;
            }

            cout << "-----------------------------------------------------------" << endl;

            // Prompt user to choose a category
            int categoryChoice;
            cout << "Enter the number corresponding to the category you want to display: ";
            cin >> categoryChoice;

            // Validate category choice
            if (categoryChoice >= 1 && categoryChoice <= uniqueCategories.size())
            {
                // Find the category at the chosen index
                auto categoryIterator = uniqueCategories.begin();
                advance(categoryIterator, categoryChoice - 1);
                string chosenCategory = *categoryIterator;

                // Display products in the chosen category
                cout << "Products in Category \"" << chosenCategory << "\":" << endl;
                for (const auto &product : products)
                {
                    if (product.getCategory() == chosenCategory)
                    {
                        cout << "ID: " << product.getId() << endl;
                        cout << "Name: " << product.getName() << endl;
                        cout << "Category: " << product.getCategory() << endl;
                        cout << "Price: $" << product.getPrice() << endl;
                        cout << "Quantity: " << product.getQuantity() << endl;
                        cout << "-----------------------------------------------------------" << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid category choice. Please try again." << endl;
            }

            break;
        }

        case 3: {
            if (products.empty()) {
                cout << "No products available." << endl;
            } else {
                cout << "Product List:" << endl;
                cout << "-----------------------------------------------------------" << endl;
                for (const auto &product : products) {
                    cout << "ID: " << product.getId() << endl;
                    cout << "Name: " << product.getName() << endl;
                    cout << "Category: " << product.getCategory() << endl;
                    cout << "Price: $" << product.getPrice() << endl;
                    cout << "Quantity: " << product.getQuantity() << endl;
                    cout << "-----------------------------------------------------------" << endl;
                }
            }
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}
void Inventory::updateProduct()
{
    int productId;
    cout << "Enter the ID of the product you want to update: ";
    cin >> productId;

    // Find the product with the given ID
    auto productIterator = find_if(products.begin(), products.end(), [productId](const Product& product) {
        return product.getId() == productId;
    });

    if (productIterator != products.end()) {
        // Product found, prompt for attribute to update
        int choice;
        cout << "Product found: " << productIterator->getName() << " (ID: " << productIterator->getId() << ")" << endl;
        cout << "Select the attribute to update:" << endl;
        cout << "1. Name" << endl;
        cout << "2. Category" << endl;
        cout << "3. Price" << endl;
        cout << "4. Quantity" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string newName;
                cout << "Enter the new name for the product: ";
                cin.ignore(); // Ignore the newline character left in the input stream
                getline(cin, newName);
                productIterator->setName(newName);
                cout << "Product name has been updated." << endl;
                break;
            }
            case 2: {
                string newCategory;
                cout << "Enter the new category for the product: ";
                cin.ignore();
                getline(cin, newCategory);
                productIterator->setCategory(newCategory);
                cout << "Product category has been updated." << endl;
                break;
            }
            case 3: {
                double newPrice;
                cout << "Enter the new price for the product: ";
                cin >> newPrice;
                productIterator->setPrice(newPrice);
                cout << "Product price has been updated." << endl;
                break;
            }
            case 4: {
                int newQuantity;
                cout << "Enter the new quantity for the product: ";
                cin >> newQuantity;
                productIterator->setQuantity(newQuantity);
                cout << "Product quantity has been updated." << endl;
                break;
            }
            default:
                cout << "Invalid choice. No attributes have been updated." << endl;
        }
    }
    else {
        cout << "Product with ID " << productId << " not found." << endl;
    }
}

void Inventory::buyProduct()
{
    int id, quantity;
    char choice;

    do {
        cout << "Enter the ID of the product you want to buy: ";
        cin >> id;

        Product *product = findProduct(id);
        if (product == nullptr)
        {
            cout << "Product with ID " << id << " does not exist." << endl;
            continue;
        }

        cout << "Product found: " << product->getName() << " (ID: " << product->getId() << ")" << endl;
        cout << "Price: $" << product->getPrice() << endl;

        cout << "Enter the quantity you want to buy: ";
        cin >> quantity;

        if (quantity > product->getQuantity())
        {
            cout << "Quantity entered is greater than the available stock." << endl;
            continue;
        }

        product->setQuantity(product->getQuantity() - quantity);
        cout << "Total cost: $" << (product->getPrice() * quantity) << endl;
        cout << "Product purchased successfully!" << endl;

        cout << "Do you want to buy anything else? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

}


int main()
{
    Inventory inventory;

    // Load inventory from file
    inventory.loadInventoryFromFile("inventory.csv");
    inventory.loadWishlistFromFile("require.txt");
	
	  std::ofstream requireFile("require.txt");
    if (requireFile.is_open())
    {
        requireFile << "Products with stock below 5:\n";

        for (const auto& product : inventory.getProducts())
        {
            if (product.getQuantity() < 5)
            {
                requireFile << "ID: " << product.getId() << ", Name: " << product.getName() << ", Quantity: " << product.getQuantity() << "\n";
            }
        }

        requireFile.close();
    }
    else
    {
        cout << "Unable to create require.txt file." << endl;
    }
    int choice;
    bool isAdmin = false; // Flag to determine if user is admin

    cout << "Are you an admin? (y/n): ";
    char adminChoice;
    cin >> adminChoice;
    
     if (adminChoice == 'y' || adminChoice == 'Y')
    {
        isAdmin = true;

        cout << "Enter passcode: ";
        string passcode;
        cin >> passcode;

        if (passcode != "admin123") // Replace "admin123" with your desired passcode
        {
            cout << "Incorrect passcode. Access denied." << endl;
            cout << "Redirecting to Customer Menu......"<<endl;
            isAdmin = false;
        }
    }

    if (isAdmin)
    {
        do
    {
        cout << "------------------- Menu -------------------" << endl;
        cout << "1. Display Products" << endl;
        cout << "2. Add Product" << endl;
        cout << "3. Remove Product" << endl;
        cout << "4. Buy Product" << endl;
        cout << "5. Add to Wishlist" << endl;
        cout << "6. View Wishlist" << endl;
        cout << "7. Update Products" << endl;
        
        cout << "8. Return the Product" << endl;
        cout << "9. Exit" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Enter your choice (1-9): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            inventory.displayProducts();
            break;
        case 2:
        {
            int id, quantity;
            string name, category;
            double price;

            cout << "Enter product ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter product name: ";
            getline(cin, name);

            cout << "Enter product category: ";
            getline(cin, category);

            cout << "Enter product price: ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;

            Product product(id, name, category, price, quantity);
            inventory.addProduct(product);
            break;
        }
        case 3:
        {
            int id;
            cout << "Enter the ID of the product you want to remove: ";
            cin >> id;
            inventory.removeProduct(id);
            break;
        }
        case 4:
            inventory.buyProduct();
            cout<<"Thanks for the purchase"<<endl;
            break;
        case 5:
        {
            string product;
            cin.ignore();
            cout << "Enter the product you want to add to the wishlist: ";
            getline(cin, product);
            inventory.addToWishlist(product);
            break;
        }
        case 6:
            inventory.viewWishlist();
            break;
        case 7:
            inventory.updateProduct();
            break;
        case 8:
   	 inventory.returnProduct();
   	 break;

        case 9:
            // Save inventory and wishlist to files before exiting
            inventory.saveInventoryToFile("inventory.csv");
            inventory.saveWishlistToFile("require.txt");
            cout << "Exiting program..." << endl;
            break;
            
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);
    }
    else
    {
        do
        {
            cout << "------------------- Customer Menu -------------------" << endl;
            cout << "1. Display Products" << endl;
            cout << "2. Buy Product" << endl;
            cout << "3. Add to Wishlist" << endl;
            cout << "4. View Wishlist" << endl;
            cout << "5. Return the Product"<<endl;
            cout << "6. Exit" << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "Enter your choice (1-5): ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                inventory.displayProducts();
                break;
            case 2:
                inventory.buyProduct();
                cout << "Thanks for the purchase" << endl;
                break;
            case 3:{
                 string product;
            cin.ignore();
            cout << "Enter the product you want to add to the wishlist: ";
            getline(cin, product);
            inventory.addToWishlist(product);
            
                break;
                }
            case 4:
                inventory.viewWishlist();
                break;
            case 6:
                // Save inventory and wishlist to files before exiting
                inventory.saveInventoryToFile("inventory.csv");
                inventory.saveWishlistToFile("require.txt");
                
                cout << "Exiting program..." << endl;
                break;
                case 5:
   		 inventory.returnProduct();
   		 break;

            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 9);
    }

    return 0;
}

