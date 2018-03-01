#include <string>
#include <fstream>
#include <vector>

#pragma region description
struct input
{
    int R; /* horizontal rows */
    int C; /* vertical columns */

    int F; /* vechicles */

    int N; /* number of prebooked rides */

    int B; /* bonus */
    int T; /* simulation steps */
} input;
struct output
{
    int M;
    std::vector<int> R;
} output;
#pragma endregion

#pragma region data structures
struct int2
{
    int x = 0;
    int y = 0;
};

/* ride desc */
struct ride
{
    int2 start_intersection;
    int2 finish_intersection;

    int earliest_start;
    int latest_finish;
};

/* vehicle desc */
struct vehicle
{
    int2 position;
};
#pragma endregion

#pragma region data
int step = 0; /* current simulation time */

std::vector<ride> rides;
std::vector<vehicle> vehicles;
#pragma endregion

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
        ride ride;
        file >> ride.start_intersection.x;
        file >> ride.start_intersection.y;
        file >> ride.finish_intersection.x;
        file >> ride.finish_intersection.y;
        file >> ride.earliest_start;
        file >> ride.latest_finish;

        rides.push_back(ride);
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