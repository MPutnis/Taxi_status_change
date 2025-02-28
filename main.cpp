#include <iostream>
#include <vector>
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
        int getTaxiID() { return taxiID; }
        int getStatusID() { return statusID; }
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
            cout << "Taxi ID: " << getTaxiID() << "Status: " << Statuses[getStatusID()] << "Timestamp: " << timestampToString() << endl;
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
/* 3. Main function
        TODO:3a. Write some test data to test the function
        TODO:3b. Call Status Change function
        TODO:3c. Print out results
*/

