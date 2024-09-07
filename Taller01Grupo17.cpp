#include <iostream>
#include <string>

using namespace std;

struct Product
{
    string name;
    int stock;

    Product(const string &nom = "", int stockP = 0)
    {
        name = nom;
        stock = stockP;
    }
};

void updateStock(Product products[], int numProducts, const string &name, int newStock)
{
    for (int i = 0; i < numProducts; ++i)
    {
        if (products[i].name == name)
        {
            products[i].stock = newStock;
            return;
        }
    }
    cout << "Producto no encontrado: " << name << endl;
}

void sortProducts(Product products[], int numProducts)
{
    for (int i = 0; i < numProducts - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < numProducts; ++j)
        {
            if (products[j].stock < products[minIndex].stock)
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            Product temp = products[i];
            products[i] = products[minIndex];
            products[minIndex] = temp;
        }
    }
}

void getLowStock(Product products[], int numProducts, int n)
{
    sortProducts(products, numProducts);

    int lowStockProducts = 0;
    for (int i = 0; i < numProducts; ++i)
    {
        if (products[i].stock <= 10)
        {
            lowStockProducts++;
        }
        else
        {
            break;
        }
    }

    if (lowStockProducts == 0)
    {
        cout << "No hay productos con stock igual o menor a 10." << endl;
        return;
    }

    if (n > lowStockProducts)
    {
        n = lowStockProducts;
    }

    cout << "Los " << n << " productos con menor stock (menor o igual a 10) son:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Nombre: " << products[i].name << ", Stock: " << products[i].stock << endl;
    }
}

void showMenu(Product* &products, int &numProducts)
{
    int opt = 0;
    while (opt!=4)
    {
        cout << "\n--- Menú ---\n";
        cout << "1. Ingresar productos\n";
        cout << "2. Mostrar productos con menor stock\n";
        cout << "3. Actualizar stock de un producto\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opt;

        switch (opt)
        {
        case 1:
        {
            int newProducts;
            cout << "Ingrese el número de productos a agregar: ";
            cin >> newProducts;

            if (newProducts <= 0)
            {
                cout << "Número de productos debe ser mayor que 0." << endl;
                break;
            }

            int newSize = numProducts + newProducts;
            Product* newArray = new Product[newSize];

            for (int i = 0; i < numProducts; ++i)
            {
                newArray[i] = products[i];
            }

            for (int i = numProducts; i < newSize; ++i)
            {
                cout << "Ingrese el nombre del producto " << (i + 1) << ": ";
                cin.ignore();
                getline(cin, newArray[i].name);
                cout << "Ingrese la cantidad en stock de " << newArray[i].name << ": ";
                cin >> newArray[i].stock;
            }

            delete[] products;
            products = newArray;
            numProducts = newSize;
            break;
        }
        case 2:
            cout << "Ingrese el número de productos a mostrar: ";
            int n;
            cin >> n;
            getLowStock(products, numProducts, n);
            break;
        case 3:
        {
            cout << "Ingrese el nombre del producto a actualizar: ";
            cin.ignore();
            string nameProduct;
            getline(cin, nameProduct);
            int currentStock = -1;
            for (int i = 0; i < numProducts; ++i)
            {
                if (products[i].name == nameProduct)
                {
                    currentStock = products[i].stock;
                    break;
                }
            }
            if (currentStock != -1)
            {
                cout << "Actualmente tienes: " << currentStock << " unidades de ese producto" << endl;
                cout << "Ingrese la nueva cantidad en stock para " << nameProduct << ": ";
                int newStock;
                cin >> newStock;
                updateStock(products, numProducts, nameProduct, newStock);
            }
            else
            {
                cout << "Producto no encontrado: " << nameProduct << endl;
            }
            break;
        }
        case 4:
            cout << "Saliendo del programa..." << endl;
            return;
        default:
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
            break;
        }
    }
}

int main()
{
    int numProducts = 0;
    Product* products = nullptr;
    showMenu(products, numProducts);
    delete[] products;
    return 0;
}