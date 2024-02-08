import time
start_time = time.time()
cnt = 0
for i in range(0, int(1e9)):
  cnt += 1
print(cnt)
print("--- %s seconds ---" % (time.time() - start_time))