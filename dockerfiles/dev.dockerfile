# Build this from the repository root:
#   docker build --platform linux/amd64 -t so3-dev -f dockerfiles/dev.dockerfile .
# Mount your checkout at /so3 when you run it. Game data never goes in the image.
# Python 3.12.14 on Debian 13. The digest pins the whole base image, so it
# can't change underneath us.
FROM python:3.12.14-slim-trixie@sha256:f77ac9e44ae96ef2c90b8053ea08c31f8be030f824196b0ae4db6d462c84e51f

ENV PYTHONDONTWRITEBYTECODE=1 \
    PYTHONUNBUFFERED=1 \
    PIP_DISABLE_PIP_VERSION_CHECK=1 \
    PIP_NO_CACHE_DIR=1 \
    XDG_CACHE_HOME=/tmp/so3-cache

# The release binaries below are built for x86_64 Linux. I also pin apt to a
# dated Debian snapshot. The expiry check is off because the date never moves,
# but Debian's signatures are still checked.
RUN test "$(dpkg --print-architecture)" = amd64 \
    && rm /etc/apt/sources.list.d/debian.sources \
    && printf '%s\n' \
       'deb [check-valid-until=no signed-by=/usr/share/keyrings/debian-archive-keyring.gpg] https://snapshot.debian.org/archive/debian/20260928T000000Z/ trixie main' \
       'deb [check-valid-until=no signed-by=/usr/share/keyrings/debian-archive-keyring.gpg] https://snapshot.debian.org/archive/debian/20260928T000000Z/ trixie-updates main' \
       'deb [check-valid-until=no signed-by=/usr/share/keyrings/debian-archive-keyring.gpg] https://snapshot.debian.org/archive/debian-security/20260928T000000Z/ trixie-security main' \
       > /etc/apt/sources.list \
    && apt-get update \
    && apt-get install -y --no-install-recommends build-essential ca-certificates curl file git \
    && rm -rf /var/lib/apt/lists/*

# GNU binutils v0.10 with PS2 support, including the R5900 instructions and
# Metrowerks relocations.
RUN curl --fail --location --retry 3 \
        https://github.com/decompals/binutils-mips-ps2-decompals/releases/download/v0.10/binutils-mips-ps2-decompals-linux-x86-64.tar.gz \
        -o /tmp/ps2-binutils.tar.gz \
    && echo '9fe31ea3ee1a37536f9f0e2e12c668e7c3cb99e59f5154bd2f1fc4762473094c  /tmp/ps2-binutils.tar.gz' | sha256sum -c - \
    && tar -xzf /tmp/ps2-binutils.tar.gz -C /usr/local/bin \
    && rm /tmp/ps2-binutils.tar.gz

# wibo runs the Windows compiler on Linux. I use its stable static i686 build.
# objdiff compares what I compile against the original.
RUN curl --fail --location --retry 3 \
        https://github.com/decompals/wibo/releases/download/1.2.0/wibo-i686 \
        -o /usr/local/bin/wibo \
    && echo '2575d3b0a2f408b2c2b0850db56f1af5d005a138394a6774eba77b6708ecc304  /usr/local/bin/wibo' | sha256sum -c - \
    && chmod 755 /usr/local/bin/wibo \
    && curl --fail --location --retry 3 \
        https://github.com/encounter/objdiff/releases/download/v3.8.2/objdiff-cli-linux-x86_64 \
        -o /usr/local/bin/objdiff-cli \
    && echo 'e5445089a6f707e30cb5e02992451b604619cedfd2660ee2373a86bfefd9e718  /usr/local/bin/objdiff-cli' | sha256sum -c - \
    && chmod 755 /usr/local/bin/objdiff-cli

COPY requirements.txt /opt/so3/requirements.txt
COPY dockerfiles/requirements/ /opt/so3/dockerfiles/requirements/
# Isolated builds are off, so packages that only ship as source build with the
# pinned build tools instead of whatever pip would download.
RUN python -m pip install --require-hashes --only-binary=:all: -r /opt/so3/dockerfiles/requirements/build-requirements.txt \
    && python -m pip install --require-hashes --no-build-isolation -r /opt/so3/dockerfiles/requirements/requirements.txt \
    && python -m pip check

# mwccgap is what makes INCLUDE_ASM work with the Metrowerks compiler. It's MIT
# licensed, and the license stays in /opt/mwccgap/LICENSE. My patch fixes how it
# imports relocations to local symbols, lets me choose where its temporary files
# go, and makes it skip splat's `nonmatching` marker in .rodata.
COPY dockerfiles/patches/mwccgap.patch /opt/so3/mwccgap.patch
RUN curl --fail --location --retry 3 \
        https://codeload.github.com/mkst/mwccgap/tar.gz/147598b36b198f267e80adbe04dd5804d070dbb3 \
        -o /tmp/mwccgap.tar.gz \
    && echo '8f369a064ac417af40f17cc51956ea1cbb5e8f8f85a31e3130499eca7fa2d634  /tmp/mwccgap.tar.gz' | sha256sum -c - \
    && mkdir /opt/mwccgap \
    && tar -xzf /tmp/mwccgap.tar.gz -C /opt/mwccgap --strip-components=1 \
    && cd /opt/mwccgap && git apply --check /opt/so3/mwccgap.patch \
    && git apply /opt/so3/mwccgap.patch \
    && rm /tmp/mwccgap.tar.gz

RUN mips-ps2-decompals-as --version \
    && wibo --version \
    && objdiff-cli --version \
    && ninja --version \
    && python -m splat --help > /dev/null

WORKDIR /so3
CMD ["bash"]
