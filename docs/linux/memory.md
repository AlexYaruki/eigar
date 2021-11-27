#Total physical

Did not find pure C API call to retrive this value. And `MemTotal` from `/proc/meminfo` usualy provides more or less than exact value.

The way I found to provide exact value is to check memory block size from `/sys/devices/system/memory/block_size_bytes`

Then, iterate over memory blocks directories in `/sys/bus/memory/devices/memory*`. Each block as `online` file that indicates if particular block is active.

