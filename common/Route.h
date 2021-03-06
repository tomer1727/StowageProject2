/**
 * Created by Tomer Yoeli
 * Class to represent the route of the ship
 * include all of the ports in the route and in charge of moving between them and handle their container's files
 */

#ifndef SHIPPROJECT_ROUTE_H
#define SHIPPROJECT_ROUTE_H

class Port;

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
    vector<string> portsContainersPathsSorted; // sorted vector of the containers files, base on the route (plus empty files where needed)
    map<string, int> portVisits; // How many times ports were visited
    string empty_file; // Path to an empty file for ports without containers

    /**
     * Sort the given paths for containers files base on the asked sorting formula
     * dir is the base directory and paths are relative path in this directory
     */
    void initPortsContainersFiles(const string &dir, vector<string> &paths, vector<pair<int,string>>& errVector);

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
      * Also load the containers in each port
      * dir is the base directory and paths are relative path in this directory
      */
    void initPorts(const string &dir, vector<string> &paths, vector<pair<int,string>>& errVector, const ShipPlan& ship);

    /**
     * Return if there is at least one more port in the route
     */
    bool hasNextPort() const {
        return currentPortNum < (int) (ports.size()) - 1;
    }

    /**
     * Check if the last port has waiting containers
     * @param errVector: the errors vector
     * @return true if there are
     */
    bool checkLastPortContainers(const string& lastPortPath, bool addDir);

    /**
     * Increase port number by one and invalidate containers with the same ID as containers on the ship
     * Return the true if there is at least one more port in the route
     */
    bool moveToNextPort(const ShipPlan& ship);

    Port &getCurrentPort();

    string& getCurrentPortPath(){
        return portsContainersPathsSorted[currentPortNum];
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
     * Get the ports in the route from the port with number @param fromPortNum
     * Default value is -1, means get left ports from the current one
     */
    vector<string> getLeftPortsNames(int fromPortNum = -1);

    /**
     * Sort the given containers vector by their destination, from the closest one to the farthest one
     */
    void sortContainersByDestination(vector<Container>& containers);

    /**
     * Sort the given containers vector by their destination, from the furthest one to the closest one
     */
    void sortContainersByFurtherDestination(vector<Container*>& containers);

    /**
     * Return the name of the last port
     */
    const string& getLastPortName() const;

    /**
     * Return the number of stops until @param dest (-1 if dest is not in the route)
     */
    int stopsUntilPort(const string& dest) const;

    /**
     * Return the number of ports in the route
     */
    int getNumOfPorts() const;

    /**
     * Return the number of different ports in the route (if port AAAAA appear twice it counted once)
     */
    int getNumOfDifferentPorts() const;

    /**
     * Return how many ports left in the route (not visited yet)
     */
    int stopsLeft() const;

    friend ostream &operator<<(ostream &os, const Route &r);
};

#endif //SHIPPROJECT_ROUTE_H
