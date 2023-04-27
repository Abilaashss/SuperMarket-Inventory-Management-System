#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
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
            this->id=id;
            this->name=name;
            this->category=category;
            this->price=price;
            this->quantity=quantity;
        }

        int getId() const{
            return id;
        }

        void setId(int id){
            this->id=id;
        }

        string getName() const{
            return name;
        }

        void setName(string name){
            this->name=name;
        }

        string getCategory() const{
            return category;
        }

        void setCategory(string category){
            this->category=category;
        }

        double getPrice() const{
            return price;
        }

        void setPrice(double price){
            this->price=price;
        }

        int getQuantity() const{
            return quantity;
        }

        void setQuantity(int quantity){
            this->quantity=quantity;
        }
};

class Inventory
{
    private:
        vector<Product> products;
    
    public:
        void buyProduct()
    {
        int id, quantity;
        cout << "Enter the ID of the product you want to buy: ";
        cin >> id;

        Product* product = findProduct(id);
        if (product == nullptr)
        {
            cout << "Product with ID " << id << " does not exist." << endl;
            return;
        }

        cout << "Product found: " << product->getName() << " (ID: " << product->getId() << ")" << endl;
        cout << "Price: $" << product->getPrice() << endl;

        cout << "Enter the quantity you want to buy: ";
        cin >> quantity;

        if (quantity > product->getQuantity())
        {
            cout << "Quantity entered is greater than the available stock." << endl;
            return;
        }

        product->setQuantity(product->getQuantity() - quantity);
        cout << "Total cost: $" << (product->getPrice() * quantity) << endl;
        cout << "Product purchased successfully!" << endl;
    }
	void addProduct(Product product)
        {
            bool found = false;
            for (auto& p : products)
            {
                if (p.getId() == product.getId())
                {
                    cout << "Id already Exist."<< endl;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                products.push_back(product);
                cout << "Product added successfully." << endl;
                cout << "-----------------------------------------------------------" <<endl;
            }
        }    
        vector<Product>& getProducts() {
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
                    cout << "-----------------------------------------------------------" <<endl;
                    break;
                }
            }
            if (!found)
            {
                cout << "Id does not exist" << endl;
            }
        }

        Product* findProduct(int id)
        {
            for(auto i=products.begin();i!=products.end();i++)
            {
                if(i->getId()==id)
                {
                    return &(*i);
                }
            }
            return nullptr;
        }

        void updateProduct(int id, string name, string category, double price, int quantity)
        {
            bool found = false;
            for (auto i = products.begin(); i != products.end(); i++)
            {
                if (i->getId() == id)
                {
                    i->setName(name);
                    i->setCategory(category);
                    i->setPrice(price);
                    i->setQuantity(quantity);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "ID does not exist." << endl;
            }
        }        

        void printProduct() const{
            for(auto i=products.begin();i!=products.end();i++)
            {
                cout<<"ID : "<<i->getId()<<endl;
                cout<<"Name : "<<i->getName()<<endl;
                cout<<"Category : "<<i->getCategory()<<endl;
                cout<<"Price : $"<<i->getPrice()<<endl;
                cout<<"Quantity : "<<i->getQuantity()<<endl;
            }
        }

        void saveInventoryToFile(string filename) 
        {
            ofstream file;
            file.open(filename, ios::out | ios::app);
            for (int i = 0; i < products.size(); i++) 
            {
                Product p = products[i];
                file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << endl;
            }
            file.close();
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
};

int main() {
    Inventory inventory;
    cout << "-----------------------------------------------------------" <<endl;
    cout << "---------------Inventory Management System ----------------" <<endl;   
    cout << "-----------------------------------------------------------" <<endl;
    cout << "------------------------- Welcome! ------------------------" <<endl;
    cout << "-----------------------------------------------------------" <<endl;
    inventory.loadInventoryFromFile("inventory.csv");
    char choice;
    char choice1,choice2;
    cout << "Are you a customer(y/n)?" << endl;
    cin>>choice1;
    if(choice1=='y'){
        do{
            cout << "1. Find a product" << endl;
            cout << "2. View all products" << endl;
            cout<<"3. Buy Product"<<endl;
            cout << "4. Add a wishlist" << endl;
            cout << " Q. Quit" << endl;
            cin>>choice2>>endl;
            
            
            switch(choice2){
                case '1': {
            char searchOption;
            cout << "Search by:\n";
            cout << "1. ID\n";
            cout << "2. Category\n";
            cout << "Enter your choice: ";
            cin >> searchOption;

            if (searchOption == '1') {
                int id;
                cout << "Enter product ID: ";
                cin >> id;

                Product* product = inventory.findProduct(id);
                if (product) {
                    cout << "Name: " << product->getName() << endl;
                    cout << "Category: " << product->getCategory() << endl;
                    cout << "Price: $" << product->getPrice() << endl;
                    cout << "Quantity: " << product->getQuantity() << endl;
                    cout << "-----------------------------------------------------------" << endl;
                } else {
                    cout << "Product not found." << endl;
                    cout << "-----------------------------------------------------------" << endl;
                }
            } else if (searchOption == '2') {
                string category;
                cout << "Enter product category: ";
                cin >> category;

                bool productFound = false;
                for (auto& product : inventory.getProducts()) {
                    if (product.getCategory() == category) {
                        cout << "ID: " << product.getId() << endl;
                        cout << "Name: " << product.getName() << endl;
                        cout << "Category: " << product.getCategory() << endl;
                        cout << "Price: $" << product.getPrice() << endl;
                        cout << "Quantity: " << product.getQuantity() << endl;
                        cout << "-----------------------------------------------------------" << endl;
                        productFound = true;
                    }
                }

                if (!productFound) {
                    cout << "No products found in the given category." << endl;
                    cout << "-----------------------------------------------------------" << endl;
                }
            } else {
                cout << "Invalid choice. Please try again." << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            break;
        }
                case '2': {
                    inventory.printProduct();
                    break;
             }
                    
                    
                    
            }
        }
    }
    else if(choice1=='n'){
    
    do {
        
        cout << "Please choose an option:" << endl;
        cout << "1. Add a product" << endl;
        cout << "2. Remove a product" << endl;
        cout << "3. Find a product" << endl;
        cout << "4. Update a product" << endl;
        cout << "5. View all products" << endl;
        cout<<"6. Buy Product"<<endl; 
        cout << "7. Add a wishlist" << endl;
        cout << "8. View wishlist" << endl;
	cout << "Q. Quit" << endl;
        cin >> choice;

        switch (choice) {
        case '1': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product category: ";
            cin >> category;
            cout << "Enter product price: $ ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            Product product(id, name, category, price, quantity);
            inventory.addProduct(product);
            break;
        }

        case '2': {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            inventory.removeProduct(id);
            break;
        }

        case '3': {
    char searchOption;
    cout << "Search by:\n";
    cout << "1. ID\n";
    cout << "2. Category\n";
    cout << "Enter your choice: ";
    cin >> searchOption;

    if (searchOption == '1') {
        int id;
        cout << "Enter product ID: ";
        cin >> id;

        Product* product = inventory.findProduct(id);
        if (product) {
            cout << "Name: " << product->getName() << endl;
            cout << "Category: " << product->getCategory() << endl;
            cout << "Price: $" << product->getPrice() << endl;
            cout << "Quantity: " << product->getQuantity() << endl;
            cout << "-----------------------------------------------------------" << endl;
        } else {
            cout << "Product not found." << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    } else if (searchOption == '2') {
        string category;
        cout << "Enter product category: ";
        cin >> category;

        bool productFound = false;
        for (auto& product : inventory.getProducts()) {
            if (product.getCategory() == category) {
                cout << "ID: " << product.getId() << endl;
                cout << "Name: " << product.getName() << endl;
                cout << "Category: " << product.getCategory() << endl;
                cout << "Price: $" << product.getPrice() << endl;
                cout << "Quantity: " << product.getQuantity() << endl;
                cout << "-----------------------------------------------------------" << endl;
                productFound = true;
            }
        }

        if (!productFound) {
            cout << "No products found in the given category." << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
        cout << "-----------------------------------------------------------" << endl;
    }
    break;
}	

        case '4': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter the product id: ";
            cin >> id;
            cout << "Enter new product name: ";
            cin >> name;
            cout << "Enter new product category: ";
            cin >> category;
            cout << "Enter new product price: $ ";
            cin >> price;
            cout << "Enter new product quantity: ";
            cin >> quantity;
            inventory.updateProduct(id, name, category, price, quantity);
            cout << "Product updated successfully." << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }

        case '5': {
            inventory.printProduct();
            break;
     }
	case '6':{
		inventory.buyProduct();
    		break;
		 }
	case '7':
	{
    	string wishlist;
    	cin.ignore();
    	cout << "Enter your wishlist (separated by commas): ";
    	getline(cin, wishlist);
	
	    ofstream file("require.csv", ios::out | ios::app);
	    if (file.is_open()) {
	        file << wishlist << endl;
	        file.close();
	        cout << "Wishlist added successfully." << endl;
	        cout << "-----------------------------------------------------------" << endl;
	    } else {
	        cout << "Error: Could not open file require.csv" << endl;
	    }
	    break;
	}
	case '8':
	{
	    ifstream file("require.csv");
	    if (file.is_open()) {
	        string line;
	        while (getline(file, line)) {
	            cout << "Wishlist: " << line << endl;
	        }
	        file.close();
	        cout << "-----------------------------------------------------------" << endl;
	    } else {
	        cout << "Error: Could not open file require.csv" << endl;
	    }
	    break;
	}

        case 'q':
        case 'Q':
            cout << "Goodbye!" << endl;
            inventory.saveInventoryToFile("inventory.csv");
            cout << "-----------------------------------------------------------" <<endl;
            return 0;
        
        default:
            cout << "Invalid Choice. Please Try again" << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
    } while (true);
        

    return 0;
}

