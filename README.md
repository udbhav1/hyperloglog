# HyperLogLog

Inspired by https://www.youtube.com/watch?v=YA-nB2wjVcI

Uses a little-endian only implementation of [xxhash32](https://create.stephan-brumme.com/xxhash/)

Memory benchmarked with `getRusage()` on Linux and `task_info()` on OSX, averaged over five runs

## Usage
```
make
./hlltest
./naive
```

## Benchmarks

### Memory

| Data                          | Naive Set | HyperLogLog | Improvement |
|-------------------------------|-----------|-------------|------------ |
| Shakespeare's collected works |  1919 kB  | 45.06 kB    | 43x         |

### Accuracy

| Data                          | Naive Set | HyperLogLog | Error |
|-------------------------------|-----------|-------------|------ |
| Shakespeare's collected works |  28756    | 29275.6     | 1.8%   |
