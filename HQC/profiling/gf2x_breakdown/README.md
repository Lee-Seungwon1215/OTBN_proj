# HQC-1 `vect_mul` stage profiler

This profiler measures mutually exclusive regions inside the reference GF(2)
polynomial multiplication implementation:

- schoolbook leaf multiplication;
- Karatsuba operand preparation;
- Karatsuba result assembly;
- reduction modulo `X^PARAM_N - 1`;
- residual recursive dispatch and profiling overhead.

The normal build is unchanged. Profiling is compiled only when
`HQC_GF2X_PROFILE=ON`, and it is supported only for `HQC_ARCH=ref`.

## Build and run on Ubuntu

```sh
cmake -S . -B /tmp/hqc-gf2x-profile -G Ninja \
  -DHQC_ARCH=ref \
  -DHQC_GF2X_PROFILE=ON \
  -DCMAKE_BUILD_TYPE=Release

cmake --build /tmp/hqc-gf2x-profile \
  --target profile_gf2x_hqc_1 \
  -j 4

/tmp/hqc-gf2x-profile/tests/bench/profile_gf2x_hqc_1 100 10
```

The first positional argument is the number of measured KEM operations. The
second is the number of warm-up keygen/encaps/decaps sequences. Output is CSV,
with one row each for key generation, encapsulation, and decapsulation.

The executable checks that the encapsulated and decapsulated shared secrets
match. The counters are process-global and are intended for single-threaded
profiling only.

## Initial Apple M2 result

Configuration: AppleClang 21, `Release` (`-O3`), five independent trials, 30
measured operations per KEM phase and three warm-up sequences. Values below are
the medians of the five trials.

| Phase | `vect_mul` / KEM | Schoolbook / `vect_mul` | Karatsuba prepare | Karatsuba assemble | Reduction | Residual |
|---|---:|---:|---:|---:|---:|---:|
| Keygen | 97.942% | 98.197% | 0.315% | 0.483% | 0.008% | 0.965% |
| Encaps | 97.776% | 98.208% | 0.311% | 0.482% | 0.008% | 0.971% |
| Decaps | 95.825% | 98.179% | 0.306% | 0.532% | 0.008% | 0.984% |

Per `vect_mul` call, the deterministic operation counters report:

| Counter | Count |
|---|---:|
| Karatsuba calls, including leaves | 364 |
| Karatsuba internal calls | 121 |
| Schoolbook leaf calls | 243 |
| Schoolbook inner word iterations | 1,219,456 |
| Karatsuba prepare word iterations | 1,873 |
| Karatsuba assemble word iterations | 11,104 |
| Reduction word iterations | 277 |

These timings identify the current C implementation's schoolbook leaf as the
dominant `vect_mul` region. They are host measurements, not projected OTBN cycle
shares; the same profiler should be rerun on the Ubuntu machine for the final
host baseline.
