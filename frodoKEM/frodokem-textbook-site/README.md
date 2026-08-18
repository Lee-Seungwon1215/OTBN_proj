# FrodoKEM Co-Design Atlas

`FrodoKEM-640-SHAKE`의 함수 흐름, 실측 프로파일, 병목 반복문과 RISC-V·OTBN ISA 비용모델을 연결하는 인터랙티브 한국어 성능 교재입니다.

## 교재 구성

- 알고리즘·파라미터·구현체 확정
- KeyGen / Encaps / Decaps 함수·region 흐름
- REFERENCE와 FAST_GENERIC 100회 × 9 trials 비교
- 병목 반복문의 정확한 trip count와 구현별 시간 비중
- SHAKE, MAC16, CDF, 직렬화 primitive 선정
- RV32IM+Zbb, RVV128, OTBN+KMAC, OTBN MAC16 제안 비교
- Amdahl 기반 인터랙티브 가속 상한 모델

## 실행

```bash
npm install
npm run dev
```

배포용 결과를 확인하려면 `npm run build`, 전체 스모크 테스트는 `npm test`를 실행합니다.
