import sys
import heapq
input = sys.stdin.readline

def solve():
    N, K = map(int, input().split())
    events = []
    items = []
    
    for _ in range(N):
        S, E, P, D = map(int, input().split())
        A = P + D * S
        events.append((S, +1, A, D, S))
        events.append((E + 1, -1, A, D, S))
    
    events.sort()
    
    active = []  # list of (A, D, S)
    removed = {}
    min_energy = float('inf')
    current_day = None
    
    for i, (day, typ, A, D, S) in enumerate(events):
        current_day = day
        
        # Add or remove
        if typ == +1:
            heapq.heappush(active, (A, D, S))
        else:
            removed[(A, D, S)] = True
        
        # Skip duplicate days
        if i + 1 < len(events) and events[i + 1][0] == day:
            continue
        
        # Clean up removed items
        while active and removed.get(active[0], False):
            heapq.heappop(active)
        
        # Compute all active energies at this day
        current_energies = []
        for (A_i, D_i, S_i) in active:
            energy_today = A_i - D_i * day
            current_energies.append(energy_today)
        
        if len(current_energies) < K:
            continue
        
        # Take K smallest efficiently
        largest_k = heapq.nsmallest(K, current_energies)
        total_energy = sum(largest_k)
        min_energy = min(min_energy, total_energy)
    
    print(-1 if min_energy == float('inf') else min_energy)

if __name__ == "__main__":
    solve()
