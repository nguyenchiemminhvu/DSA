## Problem

https://leetcode.com/problems/count-tested-devices-after-test-operations/

```
You are given a 0-indexed integer array batteryPercentages having length n, denoting the battery percentages of n 0-indexed devices.

Your task is to test each device i in order from 0 to n - 1, by performing the following test operations:

If batteryPercentages[i] is greater than 0:
Increment the count of tested devices.
Decrease the battery percentage of all devices with indices j in the range [i + 1, n - 1] by 1, ensuring their battery percentage never goes below 0, i.e, batteryPercentages[j] = max(0, batteryPercentages[j] - 1).
Move to the next device.
Otherwise, move to the next device without performing any test.
Return an integer denoting the number of devices that will be tested after performing the test operations in order.

Example 1:

Input: batteryPercentages = [1,1,2,1,3]
Output: 3
Explanation: Performing the test operations in order starting from device 0:
At device 0, batteryPercentages[0] > 0, so there is now 1 tested device, and batteryPercentages becomes [1,0,1,0,2].
At device 1, batteryPercentages[1] == 0, so we move to the next device without testing.
At device 2, batteryPercentages[2] > 0, so there are now 2 tested devices, and batteryPercentages becomes [1,0,1,0,1].
At device 3, batteryPercentages[3] == 0, so we move to the next device without testing.
At device 4, batteryPercentages[4] > 0, so there are now 3 tested devices, and batteryPercentages stays the same.
So, the answer is 3.

Example 2:

Input: batteryPercentages = [0,1,2]
Output: 2
Explanation: Performing the test operations in order starting from device 0:
At device 0, batteryPercentages[0] == 0, so we move to the next device without testing.
At device 1, batteryPercentages[1] > 0, so there is now 1 tested device, and batteryPercentages becomes [0,1,1].
At device 2, batteryPercentages[2] > 0, so there are now 2 tested devices, and batteryPercentages stays the same.
So, the answer is 2.

Constraints:

1 <= n == batteryPercentages.length <= 100 
0 <= batteryPercentages[i] <= 100
```

## Observations

1. **Sequential Processing**: We need to test devices in order from index 0 to n-1.

2. **Testing Condition**: A device is tested only if its current battery percentage > 0.

3. **Side Effect**: When a device is tested, all subsequent devices (indices j where j > i) have their battery reduced by 1, but never below 0.

4. **Key Insight**: Instead of actually modifying the array after each test, we can track how many times we've decremented all subsequent devices. This is equivalent to tracking how many devices we've tested so far.

5. **Optimization**: For device at index i, its effective battery level is `original_battery[i] - number_of_previous_tests`. If this is > 0, we test it and increment our test counter.

6. **Mathematical Approach**: Rather than simulating the actual array modifications, we can compute the effective battery level on-the-fly.

## Solution

1. **Initialize**: 
   - `count = 0`: tracks number of tested devices
   - `steps = 0`: tracks how many devices we've tested so far (equivalent to total decrements applied to future devices)

2. **For each device**:
   - Calculate effective battery: `b = max(0, b - steps)`
     - `steps` represents how many previous devices were tested
     - Each tested device reduces current device's battery by 1
   - If effective battery ≤ 0: skip this device
   - If effective battery > 0: 
     - Test the device (increment `count`)
     - Increment `steps` (future devices will be decremented one more time)

3. **Return** the total count of tested devices

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space

**Example Walkthrough** with `[1,1,2,1,3]`:
- Device 0: effective = max(0, 1-0) = 1 > 0 → test it, count=1, steps=1
- Device 1: effective = max(0, 1-1) = 0 ≤ 0 → skip
- Device 2: effective = max(0, 2-1) = 1 > 0 → test it, count=2, steps=2  
- Device 3: effective = max(0, 1-2) = 0 ≤ 0 → skip
- Device 4: effective = max(0, 3-2) = 1 > 0 → test it, count=3, steps=3
- Result: 3

# Tags

Array, Simulation, Greedy

