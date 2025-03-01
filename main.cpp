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

// Array to hold firms
Firm firms[] = {Firm(301), Firm(302), Firm(303)};
/* 3. Main function
        DONE:3a. Write some test data to test the function
        TODO:3b. Call Status Change function
        DONE:3c. Print out results
*/
// function to print out all firms and their taxis
void printFirms()
{
    for (Firm f: firms)
    {
        f.printFirm();
    }
}

void printFirmByID(int firmID)
{
    for (Firm f: firms)
    {
        if (f.getFirmID() == firmID)
        {
            f.printFirm();
        }
    }
}

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

    // user interface
    int roleID=0, firmID=0, taxiID=0, newStatusID=0, choice=0;
    do
    {
        cout << "1. Print all firms and their taxis" << endl;
        cout << "2. Change status" << endl;        
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
            // option to print all firms and their taxis
            case 1:
                printFirms();
                break;

            // offer to change a status for a taxi
            case 2:
                // role options:
                cout << "Choose from which role you will change status.\nValid Role IDs: " << endl;
                for (auto const& x : Roles)
                {
                    cout << x.first << ": " << x.second << endl;
                }
                cout << "Enter Role ID: ";
                cin >> roleID;

                // Valid Firm IDs
                cout << "Valid Firm IDs: " << endl;
                for( Firm f: firms)
                {
                    cout << f.getFirmID() << endl;
                }
                cout << "Enter Firm ID: ";
                cin >> firmID;

                // Valid Taxi IDs
                cout << "Valid Taxi IDs: " << endl;
                printFirmByID(firmID);
                cout << "Enter Taxi ID: ";
                cin >> taxiID;
                
                // Possible Status IDs
                cout << "Possible Statuses: " << endl;
                for (auto const& x : Statuses)
                {
                    cout << x.first << ": " << x.second << endl;
                } 
                cout << "Enter New Status ID: ";
                cin >> newStatusID;
                changeStatus(roleID, firmID, taxiID, newStatusID);
                break;
            
            // end program    
            case 3:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
                break;
        }
    } while (choice != 3);
    
    
    
    


/* Uncomment to run some tests
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
*/
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
    }
    // if Firm not found, end function
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
    // switches compare new status to current status to determine if change is valid 
    // switch cases for changes initiated by Firm
    else if (roleID == 101)
    {
        switch (newStatusID)
        {
        case 202:
            //cout << "Reached switch case: " << Roles[101] << ", "<< Statuses[202] << endl;
            // Firm  can change taxi status to waiting only from break status
            if (tempTaxi->getStatusID() == 204)
            {
                tempTaxi->setStatusID(newStatusID);
                tempTaxi->setTimestamp();
                cout << "Status changed: " << endl;
                tempTaxi->printTaxi();
            }
            else
            {
                cout << "Taxi has to be in " << Statuses[204] << " status, for Firm to change to " << Statuses[202] << " status." << endl;
            }	
            break;
        case 203:
            //cout << "Reached switch case: " << Roles[101] << ", "<< Statuses[203] << endl;
            // Firm can assign a client to a taxi that is at work and not with a client
            if (tempTaxi->getStatusID() == 202 || tempTaxi->getStatusID() == 204)
            {
                tempTaxi->setStatusID(newStatusID);
                tempTaxi->setTimestamp();
                cout << "Status changed: " << endl;
                tempTaxi->printTaxi();
            }
            else
            {
                cout << "Taxi has to be in " << Statuses[202] << " or " << Statuses[204] <<
                " status, for Firm to assign a client." << endl;
            }
            break;
        case 204:
            //cout << "Reached switch case: " << Roles[101] << ", "<< Statuses[204] << endl;
            // Taxi has to be in waiting status, for Firm to send it on break
            if (tempTaxi->getStatusID() == 202)
            {
                tempTaxi->setStatusID(newStatusID);
                tempTaxi->setTimestamp();
                cout << "Status changed: " << endl;
                tempTaxi->printTaxi();
            }
            else
            {
                cout << "Taxi has to be in " << Statuses[202] << " status, for Firm to send it on break." << endl;
            }
            break;    
        
        default:
            //cout << "Reached switch case: " << Roles[101] << ", default"<< endl;
            cout << "Invalid status." << endl;
            return;
        }
    }
    // switch cases for changes initiated by Taxi
    else if (roleID == 102)
    {
        switch (newStatusID)
        {
        case 201:
            //cout << "Reached switch case: " << Roles[102] << ", "<< Statuses[201] << endl;
            // Taxi ends work day, has to be in waiting status to end work day
            if (tempTaxi->getStatusID() == 202)
            {
                tempTaxi->setStatusID(newStatusID);
                tempTaxi->setTimestamp();
                cout << "Status changed: " << endl;
                tempTaxi->printTaxi();
            }
            else
            {
                cout << "Taxi has to be in " << Statuses[202] << " status to end work day." << endl;
            }
            break;

        case 202:
            //cout << "Reached switch case: " << Roles[102] << ", "<< Statuses[202] << endl;
            // Waiting for client, can be reached from any status
            tempTaxi->setStatusID(newStatusID);
            tempTaxi->setTimestamp();
            cout << "Status changed: " << endl;
            tempTaxi->printTaxi();
            break;

        case 203:
            //cout << "Reached switch case: " << Roles[102] << ", "<< Statuses[203] << endl;
            // Ferrying a client, can be reached( by Taxi) from waiting status
            if (tempTaxi->getStatusID() == 202)
            {
                tempTaxi->setStatusID(newStatusID);
                tempTaxi->setTimestamp();
                cout << "Status changed: " << endl;
                tempTaxi->printTaxi();
            }
            else
            {
                cout << "Taxi has to be in " << Statuses[202] << " status to ferry a client." << endl;
            }
            break;

        case 204:
            //cout << "Reached switch case: " << Roles[102] << ", "<< Statuses[204] << endl;
            // Taxi goes on a break, can be reached from waiting status
            if (tempTaxi->getStatusID() == 202)
            {
                tempTaxi->setStatusID(newStatusID);
                tempTaxi->setTimestamp();
                cout << "Status changed: " << endl;
                tempTaxi->printTaxi();
            }
            else
            {
                cout << "Taxi has to be in " << Statuses[202] << " status to go on a break." << endl;
            }
            break;

        default:
            //cout << "Reached switch case: " << Roles[102] << ", default"<< endl;
            cout << "Invalid status." << endl;
            return;
        }
    }
    else { cout << "Role not found." << endl; }
}