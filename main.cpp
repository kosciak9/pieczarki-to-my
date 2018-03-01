#include <string>
#include <fstream>
#include <vector>




struct Input
{
    int R; /* horizontal rows */
    int C; /* vertical columns */

    int F; /* vechicles */

    int N; /* number of prebooked rides */

    int B; /* bonus */
    int T; /* simulation steps */
} input;



struct Output
{
    int M;
    std::vector<int> R;
} output;




struct Int2
{
    int x = 0;
    int y = 0;
};





struct Ride
{
    Int2 start_intersection;
    Int2 finish_intersection;

    int earliest_start;
    int latest_finish;
};





struct Vehicle
{
    Int2 position;
};




int step = 0; /* current simulation time */

std::vector<Ride> rides;
std::vector<Vehicle> vehicles;





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
    std::ofstream file{ path };

    file << output.M;
    for (auto& r : output.R)
    {
        file << r;
    }
    file.close();
}





/* finds the solution to the problem */
void calculate()
{
}





int main()
{
    initialize("data/a_example.in");

    calculate();

    submit("data/a_exmaple.out");

    return 0;
}
