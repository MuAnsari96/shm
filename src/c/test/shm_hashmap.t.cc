#include "gtest/gtest.h"

extern "C" {
#include "shm.h"
#include "shm_hashmap.h"
}

/* Fixtures */
class ShmHashmapTest: public ::testing::Test {
public: 
    ShmHashmapTest() {}

    void SetUp() {
        shm_init();
    }

    void TearDown() {
        shm_close();
    }
};

/* Tests */
TEST_F(ShmHashmapTest, SetIntTest) {
    set_int_value("abc", 1);
    MapValue* mv = get_map_value("abc");

    ASSERT_EQ(mv->value.is_int, true);
    ASSERT_EQ(mv->value.is_float, false);
    ASSERT_EQ(mv->value.is_bool, false);
    ASSERT_EQ(mv->value.is_char, false);
    ASSERT_EQ(mv->value.int_value, 1);
}

TEST_F(ShmHashmapTest, SetFloatTest) {
    set_float_value("abc", 1.0);
    MapValue* mv = get_map_value("abc");

    ASSERT_EQ(mv->value.is_int, false);
    ASSERT_EQ(mv->value.is_float, true);
    ASSERT_EQ(mv->value.is_bool, false);
    ASSERT_EQ(mv->value.is_char, false);
    ASSERT_EQ(mv->value.float_value, 1.0);
}

TEST_F(ShmHashmapTest, SetBoolTest) {
    set_bool_value("abc", true);
    MapValue* mv = get_map_value("abc");

    ASSERT_EQ(mv->value.is_int, false);
    ASSERT_EQ(mv->value.is_float, false);
    ASSERT_EQ(mv->value.is_bool, true);
    ASSERT_EQ(mv->value.is_char, false);
    ASSERT_EQ(mv->value.bool_value, true);
}

TEST_F(ShmHashmapTest, SetCharTest) {
    set_char_value("abc", "def");
    MapValue* mv = get_map_value("abc");

    ASSERT_EQ(mv->value.is_int, false);
    ASSERT_EQ(mv->value.is_float, false);
    ASSERT_EQ(mv->value.is_bool, false);
    ASSERT_EQ(mv->value.is_char, true);
    ASSERT_EQ(strcmp(mv->value.char_value, "def"), 0);
}

TEST_F(ShmHashmapTest, UpdateValueTest) {
    ASSERT_EQ(set_int_value("abc", 1), true);
    ASSERT_EQ(get_map_value("abc")->value.int_value, 1);
    ASSERT_EQ(set_int_value("abc", 2), true);
    ASSERT_EQ(get_map_value("abc")->value.int_value, 2);
}

TEST_F(ShmHashmapTest, ContainsKeyTest) {
    ASSERT_EQ(contains_key("abc"), false);
    set_int_value("abc", 1);
    ASSERT_EQ(contains_key("abc"), true);
}

TEST_F(ShmHashmapTest, DeleteKeyTest) {
    ASSERT_EQ(contains_key("abc"), false);
    set_int_value("abc", 1);
    ASSERT_EQ(contains_key("abc"), true);
    ASSERT_EQ(delete_key("abc"), true);
    ASSERT_EQ(contains_key("abc"), false);
}

TEST_F(ShmHashmapTest, DeleteInvalidKeyTest) {
    ASSERT_EQ(contains_key("abc"), false);
    ASSERT_EQ(delete_key("abc"), false);
}
