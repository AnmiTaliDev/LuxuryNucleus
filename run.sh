#!/usr/bin/env bash
set -e

project_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
build_dir="${project_root}/build"

mkdir -p "${build_dir}"
cmake -S "${project_root}" -B "${build_dir}" -Darch=x86 -Darch_bit_capacity=32
cmake --build "${build_dir}"

rm -f "${build_dir}/test.iso"
mkdir -p "${project_root}/ISO/boot"
rm -f "${project_root}/ISO/boot/lnucleus.elf"
mv "${build_dir}/arch/lnucleus.elf" "${project_root}/ISO/boot/"
grub-mkrescue -o "${build_dir}/test.iso" "${project_root}/ISO/"

qemu-system-x86_64 -enable-kvm -cpu host -machine q35 -m 4G -cdrom "${build_dir}/test.iso"
