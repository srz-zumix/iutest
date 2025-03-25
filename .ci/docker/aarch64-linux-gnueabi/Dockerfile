FROM multiarch/qemu-user-static:x86_64-aarch64 as qemu
FROM conanio/gcc9-armv8
COPY --from=qemu /usr/bin/qemu-aarch64-static /usr/bin
