#include "Collections.h"
#include <gtest/gtest.h>

using namespace torchlight::Collections;

TEST(Map, BasicOperations) {
    Map<int, std::string> map;

    // 测试初始状态
    ASSERT_TRUE(map.Empty());
    ASSERT_EQ(map.Size(), 0);

    // 测试Put和Contains
    map.Put(1, "one");
    map.Put(2, "two");
    ASSERT_TRUE(map.Contains(1));
    ASSERT_TRUE(map.Contains(2));
    ASSERT_FALSE(map.Contains(3));

    // 测试Get
    ASSERT_EQ(map.Get(1), "one");
    ASSERT_EQ(map.Get(2), "two");
    ASSERT_THROW(map.Get(3), std::runtime_error);

    // 测试Remove
    map.Remove(1);
    ASSERT_FALSE(map.Contains(1));
    ASSERT_THROW(map.Remove(1), std::runtime_error);

    // 测试Clear
    map.Clear();
    ASSERT_TRUE(map.Empty());
    ASSERT_EQ(map.Size(), 0);
}

TEST(Map, KeysAndValues) {
    Map<int, std::string> map;
    map.Put(1, "one");
    map.Put(2, "two");
    map.Put(3, "three");

    // 测试Keys
    List<int> keys = map.Keys();
    ASSERT_EQ(keys.Size(), 3);
    ASSERT_TRUE(keys.Contains(1));
    ASSERT_TRUE(keys.Contains(2));
    ASSERT_TRUE(keys.Contains(3));

    // 测试Values
    List<std::string> values = map.Values();
    ASSERT_EQ(values.Size(), 3);
    ASSERT_TRUE(values.Contains("one"));
    ASSERT_TRUE(values.Contains("two"));
    ASSERT_TRUE(values.Contains("three"));
}

TEST(Map, Entries) {
    Map<int, std::string> map;
    map.Put(1, "one");
    map.Put(2, "two");

    List<MapEntry<int, std::string>> entries = map.Entries();
    ASSERT_EQ(entries.Size(), 2);
    ASSERT_EQ(entries.Get(0).Key(), 1);
    ASSERT_EQ(entries.Get(0).Value(), "one");
    ASSERT_EQ(entries.Get(1).Key(), 2);
    ASSERT_EQ(entries.Get(1).Value(), "two");
}

TEST(Map, UpdateExistingEntry) {
    Map<int, std::string> map;
    map.Put(1, "one");
    map.Put(1, "uno");

    ASSERT_EQ(map.Get(1), "uno");
    ASSERT_EQ(map.Size(), 1);
}