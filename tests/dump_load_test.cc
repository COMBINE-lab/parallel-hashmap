#include <vector>

#include "gtest/gtest.h"

#include "parallel_hashmap/phmap_dump.h"

namespace phmap {
namespace priv {
namespace {

TEST(DumpLoad, FlatHashSet_uint32) {
    phmap::flat_hash_set<uint32_t> st1 = { 1991, 1202 };

    {
        std::ofstream ofile("./dump.data", std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
        phmap::BinaryOutputArchive ar_out(std::move(ofile));
        EXPECT_TRUE(st1.phmap_dump(ar_out));
    }

    phmap::flat_hash_set<uint32_t> st2;
    {
        std::ifstream ifile("./dump.data", std::ofstream::in | std::ofstream::binary);
        phmap::BinaryInputArchive ar_in(std::move(ifile));
        EXPECT_TRUE(st2.phmap_load(ar_in));
    }
    EXPECT_TRUE(st1 == st2);
}

TEST(DumpLoad, FlatHashMap_uint64_uint32) {
    phmap::flat_hash_map<uint64_t, uint32_t> mp1 = {
        { 78731, 99}, {13141, 299}, {2651, 101} };

    {
        phmap::BinaryOutputArchive ar_out("./dump.data");
        EXPECT_TRUE(mp1.phmap_dump(ar_out));
    }

    phmap::flat_hash_map<uint64_t, uint32_t> mp2;
    {
        phmap::BinaryInputArchive ar_in("./dump.data");
        EXPECT_TRUE(mp2.phmap_load(ar_in));
    }

    EXPECT_TRUE(mp1 == mp2);
}

TEST(DumpLoad, ParallelFlatHashMap_uint64_uint32) {
    phmap::parallel_flat_hash_map<uint64_t, uint32_t> mp1 = {
        {99, 299}, {992, 2991}, {299, 1299} };

    {
        phmap::BinaryOutputArchive ar_out("./dump.data");
        EXPECT_TRUE(mp1.phmap_dump(ar_out));
    }

    phmap::parallel_flat_hash_map<uint64_t, uint32_t> mp2;
    {
        phmap::BinaryInputArchive ar_in("./dump.data");
        EXPECT_TRUE(mp2.phmap_load(ar_in));
    }
    EXPECT_TRUE(mp1 == mp2);
}

}
}
}

