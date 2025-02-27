/**
The highway adjacent to Farmer John's farm has recently seen a dramatic increase in traffic, or at least so it seems to Farmer John. To be sure, he wants to measure the traffic flow on the highway with a set of sensors, each capable of measuring the rate of flow of traffic on a segment of road.

Unfortunately, while walking through the barn one day, Farmer John trips and drops his box of sensors into a large vat of milk, after which they no longer work as well. Instead of producing a single exact reading of traffic flow rate, each sensor now outputs a range of possible values. For example, a sensor might output the range [7,13], indicating that the rate of traffic flow on a segment of road is no less than 7, and no greater than 13.

The highway runs for N miles next to the farm, and traffic on the highway only flows in one direction, from mile 1 towards mile N. Farmer John wants to install N sensors -- one for each 1-mile segment of the highway. In some of these segments, there are on-ramps that allow traffic to enter the highway; in each of these cases, Farmer John will install his sensor on the on-ramp to measure (approximately) the amount of incoming traffic. In some segments there are off-ramps that allows traffic to exit the highway; in each of these cases, Farmer John will install his sensor on the off-ramp. Each segment contains at most one ramp. If there is no on-ramp or off-ramp in a segment of highway, Farmer John installs a sensor on the main highway itself.

Given the readings from Farmer John's N sensors, please determine the most specific possible ranges that describe the rate of traffic flow initially on the highway prior to mile 1 and for traffic continuing on the highway past mile N. These ranges should be consistent with all N sensor readings.

INPUT FORMAT (file traffic.in):
The first line of input contains N (1≤N≤100). Each of the remaining N lines describes a 1-mile segment of the road, in order from mile 1 to mile N. Each line contains a string that is either "on" (if there is an on-ramp on this segment), "off" (if there is an off-ramp), or "none" (if there is no ramp), followed by two integers in the range 0…1000, indicating the lower and upper endpoints of the sensor range from this segment. If the segment contains a ramp, the sensor reading is from the ramp. Otherwise, it is from the main highway. At least one of the highway segments will be designated as "none".
OUTPUT FORMAT (file traffic.out):
The first line of output should contain two integers giving the most specific range possible for the rate of traffic flow prior to mile 1. The second line of output should contain two integers giving the most specific range possible for the rate of traffic flow after mile N. A valid solution is always guaranteed to exist.
 */

#include <iostream>
#include <vector>
#include <tuple>
#include <cstdio>

using namespace std;

#define LARGE (1000000000)

class Solution
{
public:
    void measuringTraffic(const std::vector<std::tuple<std::string, int, int>> &sensors)
    {
        // go from right to left, measure the left_low and left_high at before 1 mile
        int left_low = 0;
        int left_high = LARGE;
        for (int i = sensors.size() - 1; i >= 0; i--)
        {
            int possible_low = std::get<1>(sensors[i]);
            int possible_high = std::get<2>(sensors[i]);

            if (std::get<0>(sensors[i]) == "on")
            {
                // it is because having an on-ramp range before getting current left_low and left_high, we need to minus the range from the left_low and left_high to get the possible left_low and left_high before on-ramp
                left_low -= possible_high;
                left_high -= possible_low;
                left_low = std::max(0, left_low);
            }
            else if (std::get<0>(sensors[i]) == "off")
            {
                // it is because having an off-ramp range before getting current left_low and left_high, we need to add the range from the left_low and left_high to get the possible left_low and left_high before off-ramp
                left_low += possible_low;
                left_high += possible_high;
            }
            else
            {
                left_low = std::max(left_low, possible_low);
                left_high = std::min(left_high, possible_high);
            }
        }

        std::cout << left_low << " " << left_high << std::endl;

        // go from left to right, measure the right_low and right_high at after N mile
        int right_low = 0;
        int right_high = LARGE;
        for (int i = 0; i < sensors.size(); i++)
        {
            int possible_low = std::get<1>(sensors[i]);
            int possible_high = std::get<2>(sensors[i]);

            if (std::get<0>(sensors[i]) == "on")
            {
                // it is because having an on-ramp range, the current right_low and right_high will be the sum of the range from the possible_low and possible_high
                right_low += possible_low;
                right_high += possible_high;
            }
            else if (std::get<0>(sensors[i]) == "off")
            {
                // it is because having an off-ramp range, the current right_low and right_high will be the minus of the range from the possible_low and possible_high
                right_low -= possible_high;
                right_high -= possible_low;
                right_low = std::max(0, right_low);
            }
            else
            {
                right_low = std::max(right_low, possible_low);
                right_high = std::min(right_high, possible_high);
            }
        }

        std::cout << right_low << " " << right_high << std::endl;
    }
};

int main()
{
    freopen("traffic.in", "r", stdin);
    freopen("traffic.out", "w", stdout);

    int n;
    std::cin >> n;

    std::vector<std::tuple<std::string, int, int>> sensors(n);
    for (int i = 0; i < n; i++)
    {
        std::string s;
        int a, b;
        std::cin >> s >> a >> b;

        sensors[i] = std::make_tuple(s, a, b);
    }

    Solution sol;
    sol.measuringTraffic(sensors);

    return 0;
}