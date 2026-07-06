const std = @import("std");
const builtin = @import("builtin");

// Automatically export custom mmap/munmap/get_exe_dir compatibility layers if targeting Windows
comptime {
    if (builtin.os.tag == .windows) {
        @export(&windows_mmap, .{ .name = "mmap", .linkage = .strong });
        @export(&windows_munmap, .{ .name = "munmap", .linkage = .strong });
        @export(&windows_get_exe_dir, .{ .name = "get_exe_dir", .linkage = .strong });
    }
}

const MEM_COMMIT = 0x00001000;
const MEM_RESERVE = 0x00002000;
const PAGE_READWRITE = 0x04;
const MEM_RELEASE = 0x00008000;

fn windows_mmap(addr: ?*anyopaque, alloc_length: usize, prot: c_int, flags: c_int, fd: c_int, offset: i64) callconv(.c) ?*anyopaque {
    _ = addr;
    _ = prot;
    _ = flags;
    _ = fd;
    _ = offset;

    const result = std.os.windows.kernel32.VirtualAlloc(
        null,
        alloc_length,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE,
    );

    if (result == null) return null;
    return result;
}

fn windows_munmap(addr: ?*anyopaque, alloc_length: usize) callconv(.c) c_int {
    _ = alloc_length;
    if (addr == null) return 0;

    const result = std.os.windows.kernel32.VirtualFree(
        addr.?,
        0,
        MEM_RELEASE,
    );

    if (result == 0) return -1;
    return 0;
}

fn windows_get_exe_dir(out_buf: [*c]u8, max_len: i64) callconv(.c) i64 {
    if (out_buf == null or max_len <= 0) return -1;

    var mem_buf: [4096]u8 = undefined;
    var fba = std.heap.FixedBufferAllocator.init(&mem_buf);
    const allocator = fba.allocator();

    const exe_dir = std.fs.selfExeDirPathAlloc(allocator) catch {
        return -1;
    };
    defer allocator.free(exe_dir);

    if (exe_dir.len >= @as(usize, @intCast(max_len))) {
        return -1;
    }

    @memcpy(out_buf[0..exe_dir.len], exe_dir);
    out_buf[@as(usize, @intCast(exe_dir.len))] = 0; // Null-terminate
    return 0;
}
