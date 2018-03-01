#include <string>
#include <fstream>
#include <vector>
#include <algorithm>




struct Input
{
  int R; /* horizontal rows */
  int C; /* vertical columns */

  int F; /* vechicles */

  int N; /* number of prebooked rides */

  int B; /* bonus */
  int T; /* simulation steps */
} input;




struct Int2
{
  int x = 0;
  int y = 0;
};


struct Ride;

struct Vehicle
{
  std::vector<Ride*> rides;
};


std::vector<Ride> rides;
std::vector<Vehicle> vehicles;
int currentVehicleID = 0;

struct Ride
{
  int ID;

  Int2 start_intersection;
  Int2 finish_intersection;

  int earliest_start;
  int latest_finish;


  bool canTake()
  {
    Vehicle current_vehicle = vehicles[currentVehicleID];
  }
};


struct
{
    bool operator() (const Ride& a, const Ride& b) const
    {
        return a.points > b.points;
    }
} rideComparer;









int step = 0; /* current simulation time */






/* initialized input data and structures */
void initialize(const std::string path)
{
    std::ifstream file{ path };

    /* initial parameters */
    file >> input.R;
    file >> input.C;
    file >> input.F;
    file >> input.N;
    file >> input.B;
    file >> input.T;

    /* create vehicles */
    for (int i = 0; i < input.F; ++i)
    {
        vehicles.emplace_back();
    }

    /* create rides */
    for (int i = 0; i < input.N; ++i)
    {
        Ride Ride;
        file >> Ride.start_intersection.x;
        file >> Ride.start_intersection.y;
        file >> Ride.finish_intersection.x;
        file >> Ride.finish_intersection.y;
        file >> Ride.earliest_start;
        file >> Ride.latest_finish;

        rides.push_back(Ride);
    }

    file.close();
}





/* saves output data */
void submit(const std::string& path)
{
    std::ofstream output;
    output.open(path.c_str());

    if (output.is_open()) {
        for (int i = 0; i < vehicles.size(); i++) {
            output << vehicles[i].rides.size();
            for (int j = 0; j < vehicles[i].rides.size(); j++) {
                output << vehicles[i].rides[j];
            }
            output << std::endl;
        }
    }
    output.close();
}






void calculate()
{
  while (!rides.empty())
  {
    std::sort(rides, rideComparer);

    // pick the first which we can take at all


    currentVehicleID++;
  }
}





int main()
{
    initialize("data/a_example.in");

    calculate();

    submit("data/a_exmaple.out");

    return 0;
}
