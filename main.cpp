#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <ctime>
#include <chrono>

using namespace std;
// Task list:

/* 1. Status change function
        TODO: 1a. Input data: Firm ID, Taxi ID, Role ID, NewStatus ID
        TODO:1b. Output: Change Taxi Status and Timestamp or deny any changes
        TODO:1c. Retrieve Current status id and timestamp, compare  if 
            status IDs are different, proceed if yes, else end function
        TODO:1d. Determine Role of Change initializer
        TODO:1e. If change is logical, then make change, else no changes
        TODO:1f. Maybe add a check to see if taxi belongs to firm
*/
void changeStatus(int roleID, int firmID, int taxiID, int newStatusID);
/* 2. Data lists/ Classes
        DONE:2a. Firm Class( Role ID(?), Firm ID, Taxi list)
            DONE:2aa. Taxi Class(Role ID(?), Taxi ID, Status ID, Timestamp) lists belonging to Firm
        DONE:2b. Role List
        DONE:2c. Status List     
*/
// Role map
map<int, string> Roles = 
{
    {101, "Firm"},
    {102, "Taxi"}
};

// Status map
map<int, string> Statuses = 
{
    {201, "Not Working"},
    {202, "Working, waiting for a client"},
    {203, "Working, ferrying a client"},
    {204, "Working, on a break"}
};

// Taxi class
class Taxi
{
    private:
        int roleID = 102;
        int taxiID;
        int statusID;
        // Timestamp of last status change
        chrono::time_point<chrono::system_clock> timestamp;
    public:
        // Constructor
        Taxi(int tID, int sID)
        {
            taxiID = tID;
            statusID = sID;
            setTimestamp();
        }
        // Empty constructor
        Taxi() {}

        // Destructor
        ~Taxi() {}

        // Getters
        int getTaxiID() const { return taxiID; }
        int getStatusID() const { return statusID; }
        chrono::time_point<chrono::system_clock> getTimestamp() { return timestamp; }

        // Setters
        void setStatusID(int sID) { statusID = sID; }
        void setTimestamp() { timestamp = chrono::system_clock::now(); }

        // Convert timestamp to string
        string timestampToString()
        {
            time_t tt = chrono::system_clock::to_time_t(timestamp);
            string ts = ctime(&tt);
            return ts;
        }

        // Print taxi info
        void printTaxi()
        {
            cout << "Taxi ID: " << getTaxiID() << " Status: " << Statuses[getStatusID()] << " Timestamp: " << timestampToString() << endl;
        }
};

// Firm class
class Firm
{
    private:
        int roleID = 101;
        int firmID;
        vector<Taxi> taxiList;
    public:
        // Constructor
        Firm(int fID)
        {
            firmID = fID;
        }
        // Empty constructor
        Firm() {}

        // Destructor
        ~Firm() {}

        // Getters
        int getFirmID() { return firmID; }
        vector<Taxi> getTaxiList() { return taxiList; }

        // Setters
        void setFirmID(int fID) { firmID = fID; }

        // Add taxi to firm
        void addTaxi(Taxi t)
        {
            taxiList.push_back(t);
        }

        // DONE: Function to find taxi by ID
        Taxi* findTaxiByID(int taxiID)
        {
            auto it = find_if(taxiList.begin(), taxiList.end(), [taxiID](const Taxi& t)
            {
                return t.getTaxiID() == taxiID;
            });
            // Return pointer to taxi if found
            if (it != taxiList.end())
            {
                return &(*it);
            }
            else
            {
                //cout << "Taxi not found" << endl;
                return nullptr;
            }
        }
        // Print firm info
        void printFirm()
        {
            cout << "Firm ID: " << getFirmID() << endl;
            for (Taxi t: taxiList)
            {
                t.printTaxi();
            }
        }
};

// Array toi hold firms
Firm firms[] = {Firm(301), Firm(302), Firm(303)};
/* 3. Main function
        TODO:3a. Write some test data to test the function
        TODO:3b. Call Status Change function
        TODO:3c. Print out results
*/

int main()
{
    // Add taxis to firms
    firms[0].addTaxi(Taxi(30101, 201));
    firms[0].addTaxi(Taxi(30102, 202));
    firms[0].addTaxi(Taxi(30103, 203));
    firms[0].addTaxi(Taxi(30104, 204));
    firms[1].addTaxi(Taxi(30201, 201));
    firms[1].addTaxi(Taxi(30202, 202));
    firms[1].addTaxi(Taxi(30203, 203));
    firms[1].addTaxi(Taxi(30204, 204));
    firms[2].addTaxi(Taxi(30301, 201));
    firms[2].addTaxi(Taxi(30302, 202));
    firms[2].addTaxi(Taxi(30303, 203));
    firms[2].addTaxi(Taxi(30304, 204));

    // Print out firm info
    for (Firm f: firms)
    {
        f.printFirm();
    }

    // switch tests
    // firm makes change
    cout << "Firm makes change:" << endl;
    changeStatus(101, 301, 30101, 202);
    changeStatus(101, 301, 30102, 203);
    changeStatus(101, 301, 30103, 204);
    changeStatus(101, 301, 30104, 201);
    // taxi makes change
    cout << "Taxi makes change:" << endl;
    changeStatus(102, 302, 30201, 202);
    changeStatus(102, 302, 30202, 203);
    changeStatus(102, 302, 30203, 204);
    changeStatus(102, 302, 30204, 201);
    // same status change
    cout << "Same status change:" << endl;
    changeStatus(101, 303, 30301, 201);
    // firm not found
    cout << "Firm not found:" << endl;
    changeStatus(101, 304, 30401, 202);
    // taxi not found
    cout << "Taxi not found:" << endl;
    changeStatus(102, 303, 30305, 202);
    // role not found
    cout << "Role not found:" << endl;
    changeStatus(103, 303, 30301, 202);

    return 0;
}

// Function to change status, definition
void changeStatus(int roleID, int firmID, int taxiID, int newStatusID)
{
    // find Firm by Firm ID
    Firm* tempFirm = nullptr;
    for (Firm& f: firms)
    {
        if (f.getFirmID() == firmID)
        {
            tempFirm = &f;
            break;
        }
        // else 
        // {
        //     cout << "Firm not found." << endl;
        //     return;
        // }
    }
    if (tempFirm == nullptr)
    {
        cout << "Firm not found." << endl;
        return;
    }
    // find Taxi in Firms taxi list by Taxi ID
    Taxi* tempTaxi = tempFirm->findTaxiByID(taxiID);
    if (tempTaxi == nullptr)
    {
        cout << "Taxi not found." << endl;
        return;
    }
    // check if new status is different from current status
    if (tempTaxi->getStatusID() == newStatusID)
    {
        cout << "New status is the same as current status." << endl;
        return;
    }
    // if status is different proceed to logic check depending on role
    // switch cases for firm
    else if (roleID == 101)
    {
        switch (newStatusID)
        {
        case 202:
            cout << "Reached switch case: " << Roles[101] << ", "<< Statuses[202] << endl;	
            break;
        case 203:
            cout << "Reached switch case: " << Roles[101] << ", "<< Statuses[203] << endl;
            break;
        case 204:
            cout << "Reached switch case: " << Roles[101] << ", "<< Statuses[204] << endl;
            break;    
        
        default:
            cout << "Reached switch case: " << Roles[101] << ", default"<< endl;
            break;
        }
    }
    // switch cases for taxi
    else if (roleID == 102)
    {
        switch (newStatusID)
        {
        case 201:
            cout << "Reached switch case: " << Roles[102] << ", "<< Statuses[201] << endl;
            break;
        case 202:
            cout << "Reached switch case: " << Roles[102] << ", "<< Statuses[202] << endl;
            break;
        case 203:
            cout << "Reached switch case: " << Roles[102] << ", "<< Statuses[203] << endl;
            break;
        case 204:
            cout << "Reached switch case: " << Roles[102] << ", "<< Statuses[204] << endl;
            break;

        default:
            cout << "Reached switch case: " << Roles[102] << ", default"<< endl;
            break;
        }
    }
    else { cout << "Role not found." << endl; }
}