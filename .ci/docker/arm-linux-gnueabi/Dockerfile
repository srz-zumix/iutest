FROM multiarch/qemu-user-static:x86_64-arm as qemu
FROM conanio/gcc10-armv7
COPY --from=qemu /usr/bin/qemu-arm-static /usr/bin
