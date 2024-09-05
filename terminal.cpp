#include<iostream>
#include<string>
#include <random>
#include<stdexcept> 
using namespace std;
std::uniform_real_distribution<double> unif(0, 5);
std::default_random_engine re;

void change_exchange_rate(double& usd, double& eur, double& usdt, double& btc)
{
    double percent;
    int x;
    double currencies[] = { usd, eur, usdt, btc };
    for (int i = 0; i < 4; i++)
    {
        percent = unif(re);
        percent /= 100;
        percent *= currencies[i];
        x = rand() % (2);
        if (x)
        {
            currencies[i] += percent;
        }
        else
        {
            currencies[i] -= percent;
        }
    }
    usd = currencies[0];
    eur = currencies[1];
    usdt = currencies[2];
    btc = currencies[3];

}
int main()
{
    int choice = -1;
    double percent;
    double rub_ter, usd_ter, eur_ter, usdt_ter, btc_ter;
    double rub_kol, usd_kol = 0, eur_kol = 0, usdt_kol = 0, btc_kol = 0;
    double rub = 1.0, usd = 1.0 / 90, eur = 1.0 / 100, usdt = 1.0 / 91, btc = 1.0 / 5247879;
    double kol = -1;

    rub_kol = 1000000;
    rub_ter = 10000;
    usd_ter = 1000;
    eur_ter = 1000;
    usdt_ter = 1000;
    btc_ter = 1.5;

    cout << "You have several available currency pairs available\n 1) RUB / USD\n 2) RUB / EUR\n 3)USD / EUR\n 4)USD / USDT\n 5)USD / BTC\n";
    cout << "price:\n 1) 1=" << usd << "\n 2)1=" << eur << "\n 3)1=" << eur / usd << "\n 4)1=" << usdt / usd << "\n 5)1=" << btc / usd << "\n";

    double currencies[3][5] = {
        {rub ,usd, eur, usdt, btc},
        {rub_kol, usd_kol, eur_kol, usdt_kol, btc_kol},
        {rub_ter, usd_ter, eur_ter, usdt_ter, btc_ter }
    };
    int i, j, z, k;

    while (choice)
    {
        cout << "Press 0 if you want to exit \n";
        cout << "Select a pair of currencies \n";

        try {
            if (!(cin >> choice)) {
                choice = -1;
                throw invalid_argument("Invalid input: expected a number for choice");
            }

            if (!choice) break;

            cout << "Choose direct (0) or reverse exchange (1) \n";
            int val;

            if (!(cin >> val)) {
                throw invalid_argument("Invalid input: expected a number for exchange direction");
            }

            while (choice < 1 || choice > 5) {
                cout << "Incorrect input, please repeat \n";
                cin >> choice;
            }
            while (val != 0 && val != 1) {
                cout << "Incorrect input, please repeat \n";
                cin >> val;
            }

            if (choice == 1) {
                j = 0;
                k = 1;
            }
            else if (choice == 2) {
                j = 0;
                k = 2;
            }
            else if (choice == 3) {
                j = 1;
                k = 2;
            }
            else if (choice == 4) {
                j = 1;
                k = 3;
            }
            else if (choice == 5) {
                j = 1;
                k = 4;
            }
            if (val) {
                int z = j;
                j = k;
                k = z;
            }

            double difference = currencies[0][k] / currencies[0][j];

            kol = -1;
            while (kol != 0)
            {
                cout << "Press 0 if you want to exit \n";
                cout << "Select how much you want to exchange \n";
                if (!(cin >> kol)) {
                    throw invalid_argument("Invalid input: expected a number for amount to exchange");
                }

                if (!kol) break;

                if (currencies[1][j] < kol) {
                    cout << "Insufficient funds, please choose less or exit \n";
                }
                else if (currencies[2][k] < kol * difference) {
                    cout << "There are not enough funds in the terminal \n";
                }
                else {
                    currencies[1][k] += kol * difference;
                    currencies[1][j] -= kol;
                    currencies[2][k] -= kol * difference;
                    currencies[2][j] += kol;
                    change_exchange_rate(currencies[0][1], currencies[0][2], currencies[0][3], currencies[0][4]);
                    cout << "OK \n";
                    break;
                }
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "Your balance: \n";
    for (int i = 0; i < 5; i++)
    {
        cout << currencies[1][i] << "\n";
    }

    return 0;
}
