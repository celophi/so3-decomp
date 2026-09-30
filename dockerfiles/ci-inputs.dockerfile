# Private originals only. Use the context produced by make ci-inputs.
# docker build -f dockerfiles/ci-inputs.dockerfile -t so3-ci build/ci-inputs
# Build only the CI inputs with --target build-inputs. The default includes both discs.
# Keep the package private, independently of repository visibility.
FROM scratch AS build-inputs
COPY disc/ /disc/

FROM build-inputs AS full-discs
COPY SHA256SUMS /iso/SHA256SUMS
# Each layer carries at most 128 MiB from each disc. Both complete ISOs are
# preserved as ordered parts; tools/ci_inputs.py restore joins and verifies them.
COPY parts/000/iso/ /iso/
COPY parts/001/iso/ /iso/
COPY parts/002/iso/ /iso/
COPY parts/003/iso/ /iso/
COPY parts/004/iso/ /iso/
COPY parts/005/iso/ /iso/
COPY parts/006/iso/ /iso/
COPY parts/007/iso/ /iso/
COPY parts/008/iso/ /iso/
COPY parts/009/iso/ /iso/
COPY parts/010/iso/ /iso/
COPY parts/011/iso/ /iso/
COPY parts/012/iso/ /iso/
COPY parts/013/iso/ /iso/
COPY parts/014/iso/ /iso/
COPY parts/015/iso/ /iso/
COPY parts/016/iso/ /iso/
COPY parts/017/iso/ /iso/
COPY parts/018/iso/ /iso/
COPY parts/019/iso/ /iso/
COPY parts/020/iso/ /iso/
COPY parts/021/iso/ /iso/
COPY parts/022/iso/ /iso/
COPY parts/023/iso/ /iso/
COPY parts/024/iso/ /iso/
COPY parts/025/iso/ /iso/
COPY parts/026/iso/ /iso/
COPY parts/027/iso/ /iso/
COPY parts/028/iso/ /iso/
COPY parts/029/iso/ /iso/
COPY parts/030/iso/ /iso/
COPY parts/031/iso/ /iso/
COPY parts/032/iso/ /iso/
COPY parts/033/iso/ /iso/
COPY parts/034/iso/ /iso/
