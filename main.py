from collections import defaultdict

def download_update(n, k):
    parts = defaultdict(int)
    devices = defaultdict(list)
    
    for i in range(1, k+1):
        parts[i] = 0
    
    time_slots = 0
    while True:
        # Check if all devices have received all parts of the update
        if all(len(devices[i]) == k for i in range(2, n+1)):
            break
        
        for device_id in range(2, n+1):
            min_part = min(parts.keys(), key=lambda x: (parts[x], x))
            devices[device_id].append(min_part)
            parts[min_part] += 1
        
        for device_id in range(2, n+1):
            parts[devices[device_id].pop(0)] -= 1
        
        time_slots += 1
    
    return time_slots

n, k = map(int, input().split())
result = download_update(n, k)
print(result)
