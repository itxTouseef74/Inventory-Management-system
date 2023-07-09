#include <iostream>
#include <fstream>

using namespace std;
class temp
{
    string itemID, itemName;
    int itemQuantity, itemPrice;
    fstream file, file1;
    int totalAmount, quantity, itemRate;
    string search;
    char _choice;

public:
    void showAdminOptions();
    void addProduct();
    void viewProduct();
    void buyProduct();
    void deleteProduct();
    void updateProduct();
} obj;

int main()
{
    char role;

    cout << "Are you an Admin (A) or a Customer (C)? ";
    cin >> role;

    switch (role)
    {
    case 'A':
    case 'a':
        obj.showAdminOptions();
        break;
    case 'C':
    case 'c':
        char choice;
        cout << "Press 1 ---> Start shopping" << endl;
        cout << "Press 0 ---> Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case '1':
            obj.viewProduct();
            obj.buyProduct();
            break;
        case '0':
            system("Exit");
            break;
        default:
            cout << "Invalid Selection...😊";
            break;
        }
        break;
    default:
        cout << "Invalid Role...😊";
        break;
    }

    return 0;
}
void temp::showAdminOptions()
{
    char adminChoice;
    cout << "Press 1 ---> Add Product" << endl;
    cout << "Press 2 ---> View Products" << endl;
    cout << "Press 3 ---> Delete Product" << endl;
    cout << "Press 4 ---> Update Product" << endl;
    cout << "Press 0 ---> Exit" << endl;
    cin >> adminChoice;

    switch (adminChoice)
    {
    case '1':
        obj.addProduct();
        break;
    case '2':
        obj.viewProduct();
        break;
    case '3':
        obj.deleteProduct();
        break;
    case '4':
        obj.updateProduct();
        break;
    case '0':
        system("Exit");
        break;
    default:
        cout << "Invalid Selection...😊";
        break;
    }
}

void temp::addProduct()
{
    cout << "Enter product ID:: ";
    cin >> itemID;
    cout << "Enter Product Name::";
    cin >> itemName;
    cout << "Enter Product Quantity::";
    cin >> itemQuantity;
    cout << "Enter Item Price:: ";
    cin >> itemPrice;

    file.open("data.txt", ios::out | ios::app);
    file << itemID << "\t\t" << itemName << "\t\t" << itemQuantity << "\t\t" << itemPrice << endl;
    file.close();
}

void temp::viewProduct()
{
    file.open("data.txt", ios::in);
    file >> itemID >> itemName >> itemQuantity >> itemPrice;

    while (!file.eof())
    {
        cout << "----------------------" << endl;
        cout << "Product Id\t\tProduct Name\t\tQuantity\t\tProduct Price" << endl;
        cout << itemID << "\t\t\t" << itemName << "\t\t\t" << itemQuantity << "\t\t\t" << itemPrice << endl;
        cout << "----------------------" << endl;
        file >> itemID >> itemName >> itemQuantity >> itemPrice;
    }

    file.close();
}

void temp::buyProduct()
{
    _choice = 'y';
    while (_choice == 'y')
    {
        file.open("data.txt", ios::in);
        file1.open("temp.txt", ios::out | ios::app);
        file >> itemID >> itemName >> itemQuantity >> itemPrice;

        cout << "Enter product ID:: ";
        cin >> search;
        cout << "Enter Quantity:: ";
        cin >> quantity;

        while (!file.eof())
        {
            if (itemID == search)
            {
                if (itemQuantity > 0 && itemQuantity >= quantity)
                {
                    itemQuantity = itemQuantity - quantity;
                    file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;

                    itemRate = quantity * itemPrice;
                    totalAmount = totalAmount + itemRate;
                    cout << "---------- Payment Bill ------------" << endl;
                    cout << "Total purchase Amount: " << totalAmount << endl;
                    cout << "----- Thank You -----" << endl;
                }
                else if (itemQuantity == 0)
                {
                    cout << "Product out of stock. Cannot buy." << endl;
                    file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
                }
                else
                {
                    cout << "Insufficient stock. Cannot buy the requested quantity." << endl;
                    file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
                }
            }
            else
            {
                file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
            }
            file >> itemID >> itemName >> itemQuantity >> itemPrice;
        }

        file.close();
        file1.close();
        remove("data.txt");
        rename("temp.txt", "data.txt");

        cout << "\nContinue shopping? (Y/N): ";
        cin >> _choice;
    }
}

void temp::deleteProduct()
{
    cout << "Enter product ID to delete:: ";
    cin >> search;

    file.open("data.txt", ios::in);
    file1.open("temp.txt", ios::out);
    file >> itemID >> itemName >> itemQuantity >> itemPrice;

    while (!file.eof())
    {
        if (itemID != search)
        {
            file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
        }
        file >> itemID >> itemName >> itemQuantity >> itemPrice;
    }

    file.close();
    file1.close();
    remove("data.txt");

    rename("temp.txt", "data.txt");

    cout << "Product deleted successfully!" << endl;
}

void temp::updateProduct()
{
    cout << "Enter product ID to update:: ";
    cin >> search;

    file.open("data.txt", ios::in);
    file1.open("temp.txt", ios::out);
    file >> itemID >> itemName >> itemQuantity >> itemPrice;

    while (!file.eof())
    {
        if (itemID == search)
        {
            cout << "Enter new quantity:: ";
            cin >> itemQuantity;
            cout << "Enter new price:: ";
            cin >> itemPrice;
        }
        file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
        file >> itemID >> itemName >> itemQuantity >> itemPrice;
    }

    file.close();
    file1.close();
    remove("data.txt");
    rename("temp.txt", "data.txt");

    cout << "Product updated successfully!" << endl;
}
