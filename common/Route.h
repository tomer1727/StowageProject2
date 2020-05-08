#ifndef SHIPPROJECT_ROUTE_H
#define SHIPPROJECT_ROUTE_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <map>

#include "Port.h"
#include "Utils.h"

#define indexOfFirst_InPath (5)

using std::map;
using std::to_string;

//---Main class---//
class Route {
private:
    int currentPortNum = -1; // current port number in ports, initialize to -1 until start moving
    vector<Port> ports; // The destination in the current route
    string dir; // The directory of the files
    vector<string> portsContainersPaths; // Contain relative paths to the containers files, that have not used yet
    string currentPortPath;
    map<string, int> portVisits; // How many times ports were visited
    string empty_file; // Path to an empty file for ports without containers

public:
    // Constructors
    Route() = default;
    explicit Route(const string &path, vector<pair<int,string>>& errVector, bool& success);


    /**
     * Init the route from the given path file
     */
    void initRouteFromFile(const string &path, vector<pair<int,string>>& errVector, bool& fatalError);

    /**
     * Sort the given paths for containers files base on the asked sorting formula
     * dir is the base directory and paths are relative path in this directory
     */
    void initPortsContainersFiles(const string &dir, vector<string> &paths, vector<pair<int,string>>& errVector);

    /**
     * Return if there is at least one more port in the route
     */
    bool hasNextPort() const {
        return currentPortNum < (int) (ports.size()) - 1;
    }

    /**
     * Return the true if there is at least one more port in the route
     * Also load the waiting containers in this port
     */
    bool moveToNextPort(vector<pair<int,string>>& errVector);

    /**
     * Return the true if there is at least one more port in the route
     * Also increase port number by one
     */
    bool moveToNextPortWithoutContInit();

    Port &getCurrentPort() {
        return ports[currentPortNum];
    }

    string& getCurrentPortPath(){
        return currentPortPath;
    }

    int getNumOfVisitsInPort(string& portName){
        return portVisits[portName];
    }

    /**
     * Get the closer destination in the route between the two given ones
     */
    string getCloserDestination(const string &d1, const string &d2);

    /**
     * Check if port is in the route (searching from the current port)
     */
    bool isInRoute(const string &portName) const;

    /**
     * Sort the given containers vector by their destination, from the closest one to the farthest one
     */
    void sortContainersByDestination(vector<Container>& containers);

    friend ostream &operator<<(ostream &os, const Route &r);
};

#endif //SHIPPROJECT_ROUTE_H