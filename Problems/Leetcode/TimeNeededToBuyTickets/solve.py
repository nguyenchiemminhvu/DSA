from typing import List
from collections import deque

class Solution:
    def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
        """
        Approach 1: Queue Simulation
        Time: O(sum of all tickets), Space: O(n)
        """
        n = len(tickets)
        q = deque(tickets)
        idx = k  # Track position of person k
        steps = 0
        
        while q and q[idx] > 0:
            # Person at front buys 1 ticket
            q[0] -= 1
            steps += 1
            
            if q[0] == 0:  # Person finished buying all tickets
                if idx == 0:  # This is person k
                    return steps
                else:
                    q.popleft()  # Remove from queue
                    n -= 1
            else:
                # Move person to back of queue
                q.append(q.popleft())
            
            # Update position of person k
            idx = (idx - 1 + n) % n
        
        return steps
    
    def timeRequiredToBuyOptimized(self, tickets: List[int], k: int) -> int:
        """
        Approach 2: Mathematical Solution (Optimized)
        Time: O(n), Space: O(1)
        
        Key insight:
        - People at positions 0 to k can buy min(tickets[i], target_tickets) tickets
        - People at positions k+1 to n-1 can buy min(tickets[i], target_tickets-1) tickets
        """
        time = 0
        target_tickets = tickets[k]
        
        for i in range(len(tickets)):
            if i <= k:
                # People at or before position k (including k)
                # They have the same or more opportunities as person k
                time += min(tickets[i], target_tickets)
            else:
                # People after position k
                # They have one fewer opportunity than person k
                # (person k will finish before they get their last chance)
                time += min(tickets[i], target_tickets - 1)
        
        return time

# Test cases
def test_solution():
    sol = Solution()
    
    # Test case 1
    tickets1 = [2, 3, 2]
    k1 = 2
    result1_sim = sol.timeRequiredToBuy(tickets1, k1)
    result1_opt = sol.timeRequiredToBuyOptimized(tickets1, k1)
    print(f"Test 1 - Simulation: {result1_sim}, Optimized: {result1_opt}, Expected: 6")
    
    # Test case 2
    tickets2 = [5, 1, 1, 1]
    k2 = 0
    result2_sim = sol.timeRequiredToBuy(tickets2, k2)
    result2_opt = sol.timeRequiredToBuyOptimized(tickets2, k2)
    print(f"Test 2 - Simulation: {result2_sim}, Optimized: {result2_opt}, Expected: 8")
    
    # Additional test case
    tickets3 = [1, 1, 1, 1]
    k3 = 0
    result3_sim = sol.timeRequiredToBuy(tickets3, k3)
    result3_opt = sol.timeRequiredToBuyOptimized(tickets3, k3)
    print(f"Test 3 - Simulation: {result3_sim}, Optimized: {result3_opt}, Expected: 1")

if __name__ == "__main__":
    test_solution()