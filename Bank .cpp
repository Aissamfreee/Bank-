#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

void ShowMainMenue();

void ShowTransactions();

void ShowManageUsers();

void LoginScreen();

void ShowLoginScreen();

void ShowNoPermissionScreen();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

struct sUser
{
    string UserName;
    string Password;
    short Permission = 0;
    bool MarkForDelete = false;
    char FullAccess;
};

sUser CurrentUser;

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;


    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);  
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);
    return Client;
}

sUser ConvertLinetoRecordUser(string Line, string Seperator = "#//#")
{
    sUser User;
    vector<string> vUserData;
    vUserData = SplitString(Line, Seperator);

    User.UserName = vUserData[0];
    User.Password = vUserData[1];
    User.Permission = stoi(vUserData[2]);
    return User;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

string ConvertRecordToLine(sUser User, string Seperator = "#//#")
{

    string stUserRecord = "";
    stUserRecord += User.UserName + Seperator;
    stUserRecord += User.Password + Seperator;
    stUserRecord += to_string(User.Permission);
    return stUserRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}

bool UserExistsByUserName(string UserName, string FileName)
{

    vector <sUser> vUser;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertLinetoRecordUser(Line);
            if (User.UserName == UserName)
            {
                MyFile.close();
                return true;
            }
            vUser.push_back(User);
        }

        MyFile.close();

    }
    return false;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

vector <sUser> LoadUsersDataFromFile(string FileName)
{
    vector <sUser> vUsers;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertLinetoRecordUser(Line);
            vUsers.push_back(User);
        }
        MyFile.close();
    }
    return vUsers;
}

void PrintClientRecordLine(sClient &Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void PrintUserRecordLine(sUser &User)
{
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(12) << left << User.Permission;
}

void ShowAllUsersScreen()
{
    vector <sUser> vUser = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tUsers List (" << vUser.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(12) << "Permission";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUser.size() == 0)
        cout << "\t\t\t\tNo User Available In the System!";
    else

        for (sUser User : vUser)
        {

            PrintUserRecordLine(User);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

void PrintUserCard(sUser &User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUser Name    : " << User.UserName;
    cout << "\nPassword     : " << User.Password;
    cout << "\nPermissions  : " << User.Permission;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient>& vClients, sClient& Client)
{
    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;
}

bool FindUserByUserName(string UserName, vector <sUser>& vUser, sUser& User)
{
    for (sUser& U : vUser)
    {

        if (U.UserName == UserName)
        {
            User = U;
            return true;
        }

    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

enum  enPermission
{
    Show = 1,
    Add = 2,
    Delete = 4,
    Update = 8,
    Find = 16,
    Transactions = 32,
    ManageUser = 64,
};

sUser ChangeUserRecord(string UserName)
{
    sUser User;
    User.Permission = 0;
    User.UserName = UserName;

    cout << "\nEnter Password? ";
    getline(cin >> ws, User.Password);

    cout << "Do you want to give full access? y/n ?";
    cin >> User.FullAccess;

    if (User.FullAccess == 'Y' || User.FullAccess == 'y')
    {
        User.Permission = -1;
    }
    else
    {
        cout << "\nDo you want to give access to : ";

       char ShowClientListaccess;
        cout << "\nShow Client List? ";
        cin >>  ShowClientListaccess;
        if (ShowClientListaccess == 'Y' || ShowClientListaccess == 'y')
        {
            User.Permission = User.Permission | enPermission::Show;
        }

        char AddNewClientaccess;
        cout << "\nAdd New Client? ";
        cin >>  AddNewClientaccess;
        if (AddNewClientaccess == 'Y' || AddNewClientaccess == 'y')
        {
            User.Permission = User.Permission | enPermission::Add;
        }

        char DeleteClientaccess;
        cout << "\nDelete Client? ";
        cin >> DeleteClientaccess;
        if (DeleteClientaccess == 'Y' || DeleteClientaccess == 'y')
        {
            User.Permission = User.Permission | enPermission::Delete;
        }

        char UpdateClientaccess;
        cout << "\nUpdate Client? ";
        cin >> UpdateClientaccess;
        if (UpdateClientaccess == 'Y' || UpdateClientaccess == 'y')
        {
            User.Permission = User.Permission | enPermission::Update;
        }

        char FindClientaccess;
        cout << "\nFind Client? ";
        cin >> FindClientaccess;
        if (FindClientaccess == 'Y' || FindClientaccess == 'y')
        {
            User.Permission = User.Permission | enPermission::Find;
        }

        char Transactionsaccess;
        cout << "\nTransactions? ";
        cin >> Transactionsaccess;
        if (Transactionsaccess == 'Y' || Transactionsaccess == 'y')
        {
            User.Permission = User.Permission | enPermission::Transactions;
        }

        char ManageUseraccess;
        cout << "\nManage User? ";
        cin >>  ManageUseraccess;
        if (ManageUseraccess == 'Y' || ManageUseraccess == 'y')
        {
            User.Permission = User.Permission | enPermission::ManageUser;
        }
        
    }
    return User;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;
}

bool MarkUserForDeleteByAccountNumber(string UserName, vector <sUser>& vUser)
{

    for (sUser& U : vUser)
    {

        if (U.UserName == UserName)
        {
            U.MarkForDelete = true;
            return true;
        }

    }

    return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> &vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

    return vClients;
}

vector <sUser> SaveUsersDataToFile(string FileName, vector <sUser> &User)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (sUser U: User)
        {

            if (U.MarkForDelete == false)
            {

                DataLine = ConvertRecordToLine(U);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

    return User;
}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

sUser ReadNewUser()
{
    sUser User;
    cout << "Enter Username? ";
    getline(cin >> ws, User.UserName);

    while (UserExistsByUserName(User.UserName, UsersFileName))
    {
        cout << "\nClient with [" << User.UserName << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, User.UserName);
    }
    User = ChangeUserRecord(User.UserName);
    
    return User;
}

sUser UserLogin()
{
    
    vector <sUser> vUser = LoadUsersDataFromFile(UsersFileName);
    string UserName;
    cout << "Enter Username? ";
    getline(cin >> ws, UserName);

    string Password;
    cout << "Enter Paswword? ";
    getline(cin >> ws,Password);

    for (sUser& U : vUser)
    {
        if (U.UserName == UserName && Password == U.Password)
        {
            CurrentUser = U;
            ShowMainMenue();
            return U;
        }
    }
    system("cls");
    LoginScreen();
    cout << "Invalid Username/Password\n";
    return UserLogin();
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {

        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

void AddNewUser()
{
    sUser User;
    User = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertRecordToLine(User));
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {

        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool DeleteUserByUserName(string UserName, vector <sUser>& vUser)
{
    sUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUser, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByAccountNumber(UserName, vUser);
            SaveUsersDataToFile(UsersFileName, vUser);

            vUser = LoadUsersDataFromFile(UsersFileName);

            cout << "\n\nUser Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nUser with User Name (" << UserName << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateUserByUserName(string UserName, vector <sUser>& vUser)
{

    sUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUser, User))
    {

        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUser& U : vUser)
            {
                if (U.UserName == UserName)
                {
                    U = ChangeUserRecord(UserName);
                    break;
                }
            }

            SaveUsersDataToFile(UsersFileName, vUser);

            cout << "\n\nUser Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with User Name (" << UserName << ") is Not Found!";
        return false;
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

string ReadUserUserName()
{
    string UserName = "";

    cout << "\nPlease enter Name? ";
    cin >> UserName;
    return UserName;

}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUser Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUser = LoadUsersDataFromFile(UsersFileName);
    string UserName = ReadUserUserName();
    DeleteUserByUserName(UserName, vUser);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client  Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Users  Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUser = LoadUsersDataFromFile(UsersFileName);
    string UserName = ReadUserUserName();
    UpdateUserByUserName(UserName, vUser);

}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

void ShowAddNewUsersScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New User Screen";
    cout << "\n-----------------------------------\n";

    AddNewUsers();
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUser = LoadUsersDataFromFile(UsersFileName);
    sUser User;
    string UserName = ReadUserUserName();
    if (FindUserByUserName(UserName, vUser, User))
        PrintUserCard(User);
    else
        cout << "\nClient with User Name[" << UserName << "] is not found!";
}

void DepositAmount(vector <sClient>& vClients, sClient& Client)
{

    double Deposit;
    cout << "\nPlease enter deposit amount? \n";
    cin >> ws >> Deposit;

    char DepositMore = 'n';
    cout << "\nAre you sure want to perform; this transaction? Y/N? ";
    cin >> DepositMore;
    if (toupper(DepositMore) == 'Y')
    {
        Client.AccountBalance += Deposit;
        cout << "Done Successfull new balance is :" << Client.AccountBalance << endl;

    }

}

void showDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        DepositAmount(vClients, Client);
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == Client.AccountNumber)
            {
                C.AccountBalance = Client.AccountBalance;
                break;
            }
        }
        SaveCleintsDataToFile(ClientsFileName, vClients);

    }
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] does not exist!";
}

void WithdrawAmount(vector <sClient>& vClients, sClient& Client)
{

    double Withdraw;
    cout << "\nPlease enter Withdraw amount? \n";
    cin >> ws >> Withdraw;

    char DepositMore = 'n';
    cout << "\nAre you sure want to perform; this transaction? Y/N? ";
    cin >> DepositMore;

    if (Withdraw > Client.AccountBalance)
    {
        while (Withdraw > Client.AccountBalance)
        {
            cout << "\nAmount Exceeds the balance , you can withraw up to : ? Y/N? " << Client.AccountBalance;
            cout << "\nPlease enter Withdraw amount? \n";
            cin >> ws >> Withdraw;
        }
    }
    else
    {
        if (toupper(DepositMore) == 'Y')
        {
            Client.AccountBalance -= Withdraw;
            cout << "Done Successfull new balance is :" << Client.AccountBalance << endl;
        }
    }

}

void showWithdrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    double TotalBalance;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        WithdrawAmount(vClients, Client);
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == Client.AccountNumber)
            {
                C.AccountBalance = Client.AccountBalance;
                break;
            }
        }
        SaveCleintsDataToFile(ClientsFileName, vClients);
    }
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] does not exist!";
}

void showTotalBalanceScreen()
{
    double TotalBalances = 0;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(35) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            cout << "| " << setw(15) << left << Client.AccountNumber;
            cout << "| " << setw(40) << left << Client.Name;
            cout << "| " << setw(12) << left << Client.AccountBalance;
            cout << endl;
            TotalBalances += Client.AccountBalance;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";

    cout << "                                           Toatal Balances = " << TotalBalances << endl;
}

void LoginScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tLogin Screen ";
    cout << "\n-----------------------------------\n";
}

void ShowLoginScreen()
{
    LoginScreen();
    UserLogin();
}

void ShowNoPermissionScreen()
{
    cout << "-----------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You dont Have Permission to Do this,\n";
    cout << "Please conact Your Admin,\n";
    cout << "-----------------------------------\n";
}

enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, etransactions = 6,
    eManageuser = 7,eLogout = 8
};

enum enTransactions
{
    eDeposit = 1, eWithdraw = 2,
    eTotalBalances = 3, eMainMenu = 4,

};

enum enManageUsers
{
    eListUsers = 1, eAddNewUser = 2,
    eDeleteUser = 3, eUpdateUser = 4,
    eFindUser = 5, eMainMenue = 6
};

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}

void GoBackTransactionsMenu()
{
    cout << "\n\nPress any key to go back toTransactions Menue...";
    system("pause>0");
    ShowTransactions();

}

void GoBackManageUsersMenu()
{
    cout << "\n\nPress any key to go back to Manage Users  Menue...";
    system("pause>0");
    ShowManageUsers();

}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

short ReadTransactionsOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
} 

short ReadManageUsersOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        if (CurrentUser.Permission != -1 && !(CurrentUser.Permission & enPermission::Show))
        {
            system("cls");
            ShowNoPermissionScreen();
            GoBackToMainMenue();
        }          
        else
        {
            system("cls");
            ShowAllClientsScreen();
            GoBackToMainMenue();
        }
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        if (CurrentUser.Permission != -1 && !(CurrentUser.Permission & enPermission::Add))
        {
            system("cls");
            ShowNoPermissionScreen();
            GoBackToMainMenue();
        }      
        else
        {
            system("cls");
            ShowAddNewClientsScreen();
            GoBackToMainMenue();
        }
        break;

    case enMainMenueOptions::eDeleteClient:
        if (CurrentUser.Permission != -1 && !(CurrentUser.Permission & enPermission::Delete))
        {
            system("cls");
            ShowNoPermissionScreen();
            GoBackToMainMenue();
        }
        else
        {
            system("cls");
            ShowDeleteClientScreen();
            GoBackToMainMenue();
        }
        break;

    case enMainMenueOptions::eUpdateClient:
        if (CurrentUser.Permission != -1 && !(CurrentUser.Permission & enPermission::Update))
        {
            system("cls");
            ShowNoPermissionScreen();
            GoBackToMainMenue();
        }
        else
        {
            system("cls");
            ShowUpdateClientScreen();
            GoBackToMainMenue();
        }
        break;

    case enMainMenueOptions::eFindClient:
        if (CurrentUser.Permission != -1 && !(CurrentUser.Permission & enPermission::Find))
        {
            system("cls");
            ShowNoPermissionScreen();
            GoBackToMainMenue();
        }
        else
        {
            system("cls");
            ShowFindClientScreen();
            GoBackToMainMenue();
        }
        break;

    case enMainMenueOptions::etransactions:
        if (CurrentUser.Permission != -1 && !(CurrentUser.Permission & enPermission::Transactions))
        {
            system("cls");
            ShowNoPermissionScreen();
            GoBackToMainMenue();
        }
        else
        {
            system("cls");
            ShowTransactions();
        }
        break;

    case enMainMenueOptions::eManageuser:
        if (CurrentUser.Permission != -1 && !(CurrentUser.Permission & enPermission::ManageUser))
        {
            system("cls");
            ShowNoPermissionScreen();
            GoBackToMainMenue();
        }
        else
        {
            system("cls");
            ShowManageUsers();
        }
        break;

    case enMainMenueOptions::eLogout:
        system("cls");
        ShowLoginScreen();
        break;
    }
}

void PerfromTransactionsOption(enTransactions TransactionsOption)
{
    switch (TransactionsOption)
    {
    case enTransactions::eDeposit:
    {
        system("cls");
        showDepositScreen();
        GoBackTransactionsMenu();
        break;
    }
    case enTransactions::eWithdraw:
        system("cls");
        showWithdrawScreen();
        GoBackTransactionsMenu();

        break;

    case enTransactions::eTotalBalances:
        system("cls");
        showTotalBalanceScreen();
        GoBackTransactionsMenu();
        break;

    case enTransactions::eMainMenu:
        system("cls");
        ShowMainMenue();
        break;
    }
}

void PerfromManageUsersOption(enManageUsers MangeUsers)
{
    switch (MangeUsers)
    {
    case enManageUsers::eListUsers:
    {
        system("cls");
        ShowAllUsersScreen();
        GoBackManageUsersMenu();
        break;
    }

    case enManageUsers::eAddNewUser:
    {
        system("cls");
        ShowAddNewUsersScreen();
        GoBackManageUsersMenu();
        break;
    }

    case enManageUsers::eDeleteUser:
    {
        system("cls");
        ShowDeleteUserScreen();
        GoBackManageUsersMenu();
        break;
    }

    case enManageUsers::eUpdateUser:
    {
        system("cls");
        ShowUpdateUserScreen();
        GoBackManageUsersMenu();
        break;
    }

    case enManageUsers::eFindUser:
    {
        system("cls");
        ShowFindUserScreen();
        GoBackManageUsersMenu();
        break;
    }
    
    case enManageUsers::eMainMenue:
    {
        system("cls");
        ShowMainMenue();
        break;
    }
    }
}

void ShowTransactions()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTransactionsOption((enTransactions)ReadTransactionsOption());
}

void ShowManageUsers()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";
    PerfromManageUsersOption((enManageUsers)ReadManageUsersOption());
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client .\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{
    ShowLoginScreen();
    system("pause>0");
    return 0;
}
