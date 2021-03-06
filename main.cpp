#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>




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




struct Ride
{
    int ID;

    Int2 start_intersection;
    Int2 finish_intersection;

    int earliest_start;
    int latest_finish;


    int real_start;


    int points() const
    {
        return finish_intersection.x - start_intersection.x + finish_intersection.y - start_intersection.y;
    }

    int dist(Int2 a, Int2 b)
    {
    return abs(a.x - b.x) + abs(a.y - b.y);
    }

  bool canTake();
};


struct
{
    bool operator() (const Ride& a, const Ride& b) const
    {
        return a.points() > b.points();
    }
} rideComparer;


struct
{
    bool operator() (const Ride& a, const Ride& b) const
    {
        return a.real_start > b.real_start;
    }
} rideComparerStart;




struct Vehicle
{
  std::vector<Ride> rides;
};



bool Ride::canTake()
{
  // Vehicle current_vehicle = vehicles[currentVehicleID];
  // for (int i = 0; i < current_vehicle.rides.size()) {
  //     checkedRide = current_vehicle.rides[i];
  //     if (checkedRide.latest_finish )
  // }
  return true;
} // jak chcesz commitować to zakomentuj po prostu


std::vector<Ride> rides;
std::vector<Vehicle> vehicles;
int currentVehicleID = 0;











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
        Ride ride;
        file >> ride.start_intersection.x;
        file >> ride.start_intersection.y;
        file >> ride.finish_intersection.x;
        file >> ride.finish_intersection.y;
        file >> ride.earliest_start;
        file >> ride.latest_finish;

        ride.ID = rides.size();

        rides.push_back(ride);
    }

    file.close();
}





/* saves output data */
void submit(const std::string& path)
{
    std::ofstream output;
    output.open(path.c_str());

    if (output.is_open())
    {
      for (int i = 0; i < vehicles.size(); i++)
      {
        output << vehicles[i].rides.size() << " ";
        for (int j = 0; j < vehicles[i].rides.size(); j++)
        {
          output << vehicles[i].rides[j].ID << " ";
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
    // sort rides by how good they are, best ones first
    std::cout << "sorting rides...";
    std::sort(rides.begin(), rides.end(), rideComparer);
    std::cout << "sorted" << std::endl;

    // pick the first ride which we can take at all
    std::cout << "iterating rides..." << std::endl;
    for (int i = 0; i < rides.size(); i++)
    {
      std::cout << "\tchecking ride with ID " << rides[i].ID << "..." << std::endl;
      if (rides[i].canTake())
      {
        std::cout << "\t\ttaking ride" << std::endl;
        for (int j = 0; j < vehicles[currentVehicleID].rides.size(); j++)
        {
          if (vehicles[currentVehicleID].rides[i].end() > )
          rides[i].real_start
        }
        vehicles[currentVehicleID].rides.push_back(rides[i]);
        std::sort(vehicles[currentVehicleID].rides.begin(), vehicles[currentVehicleID].rides.end(), rideComparerStart);
        rides.erase(rides.begin() + i);
        break;
      }
    }
    std::cout << "iterated" << std::endl;

    currentVehicleID++;
  }
}





int main(int argc, const char* argv[])
{
  std::string input_file, output_file;

  if (argc == 3)
  {
    input_file = argv[1];
    output_file = argv[2];
  }
  else
  {
    std::cout << "Usage: pieczarki [file_name.in] [file_name.out]" << std::endl;
    std::cout << "Assuming files are a_example.*" << std::endl;
    input_file = "a_example.in";
    output_file = "a_example.out";
  }


  initialize(input_file);
  calculate();
  submit(output_file);

  return 0;
}
