# MemoryAnomalyBench

In this benchmark suite there are seven OpenMP benchmarks, each of which contains a known memory anomaly. These memory anomalies result from incorrect settings of OpenMP data-sharing attributes.

The evaluation results of three state-of-the-art memory anomaly detectors:

| Benchmark | Memory Anomaly | ASan | MSan | Valgrind |
|:-:|:-:|:-:|:-:|:-:|
| DSA_OMP_001 | Use of Uninitialized Memory | Undetected | Detected | Detected |
| DSA_OMP_002 | Use of Uninitialized Memory | Undetected | Detected | Detected |
| DSA_OMP_003 | Use of Uninitialized Memory | Undetected | Undetected | Detected |
| DSA_OMP_004 | Use of Uninitialized Memory | Undetected | Detected | Detected |
| DSA_OMP_005 | Use of Uninitialized Memory | Undetected | Undetected | Detected |
| DSA_OMP_006 | Use After Free | Undetected | Detected | Undetected |
| DSA_OMP_007 | Use of Stale Data | Undetected | Undetected | Undetected |
| Overall |  | 0/7 | 4/7 | 5/7 |
